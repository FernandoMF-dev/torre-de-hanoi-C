#include <stdio.h>
#include <stdlib.h>

#include "movimento-hanoi.h"

/*
Configura uma struct 'MovimentosHanoi' com valores iniciais
*/
void _inicializarMovimentoHanoi(MovimentosHanoi *movimentos, int discosQuantidade) {
    movimentos->quantidadeMax = 3 * long_pow(2, discosQuantidade);
    movimentos->quantidade = 0;
    movimentos->passos = (PassoHanoi *)malloc(movimentos->quantidadeMax * sizeof(PassoHanoi));
}

/*
Verifica se um passo em uma struct 'MovimentosHanoi' pode ser alterado para evitar movimentos desnecessários
(1)- Caso um passo pode ser conmpletamente apagado, retorna 2
    (1.1)- EXEMPLO: A => B, B => A; Nesse caso, o disco movido voltou a torre de origem
(2)- Caso o destino de um passo pode ser alterado, retona 1
    (2.1)- EXEMPLO: A => B, B => C; Nesse caso, seria melhor apenas fazer o movimento A => C
(3)- Caso nenhum desperdício tenha sido identificado, retorna 0
    (3.1)- EXEMPLO: A => B, C => A; Nesse caso, nenhum desperdício pode ser notado
*/
int _verificarDesperdicio(int dado, char* origemLabel, char* destinoLabel, MovimentosHanoi *movimentos){
    PassoHanoi passoAnterior;

    if (movimentos->quantidade > 0) {
        passoAnterior = movimentos->passos[movimentos->quantidade - 1];
        if (passoAnterior.disco == dado) {
            if (strcmp(passoAnterior.origemLabel, destinoLabel) == 0)
                return 2;
            else
                return 1;
        }
    }

    return 0;
}

/*
(1)- Retorna uma nova instância de uma struct 'PassoHanoi' já com os campos inicializados
*/
PassoHanoi _criarPasso(int disco, char *origem, char *destino) {
    PassoHanoi passo;

    passo.disco = disco;
    passo.origemLabel = origem;
    passo.destinoLabel = destino;

    return passo;
}

/*
(1)- Retorna uma nova instância de uma struct 'MovimentosHanoi' já com os campos inicializados
*/
MovimentosHanoi* criarMovimento(int maiorDisco) {
    MovimentosHanoi *movimentos = (MovimentosHanoi *)malloc(sizeof(MovimentosHanoi));

    if (movimentos == NULL){
        printf("\n\tERRO: Erro de alocação de MovimentosHanoi!\n");
        return NULL;
    }
    _inicializarMovimentoHanoi(movimentos, maiorDisco);
    
    return movimentos;
}

/*
Imprimi os valores de uma struct 'MovimentosHanoi'
*/
void imprimirMovimentosHanoi(MovimentosHanoi *movimentos) {
    printf("\n");
    for (int i = 0; i < movimentos->quantidade; i++)
        printf("\n %dº Passo: %s =(%d)=> %s", i + 1, movimentos->passos[i].origemLabel, movimentos->passos[i].disco, movimentos->passos[i].destinoLabel);
    printf("\n");
}

/*
Verifica se a quantidade de movimentos salvos numa struct 'MovimentosHanoi' ultrapassa o maximo
(1)- Se sim, retorna 1;
(2)- Se não, retona 0;
*/
int verificarMovimentoLimite(MovimentosHanoi *movimentos) {
    if (movimentos->quantidade > movimentos->quantidadeMax)
        return 1;
    return 0;
}

/*
Move uma número QUANTIDADE de itens de uma struct 'Pilha' ORIGEM para uma struct 'Pilha' DESTINO.
Isso é feito seguindo as regras do quebra da cabeça da "Torre de Hanoi".
Isso é feito usando uma struct 'Pilha' SUPORTE como auxiliar da operação
*/
void moverDisco(Pilha *origem, Pilha *destino, Pilha *suporte, int quantidade, MovimentosHanoi *movimentos) {
    int dado;

    if (quantidade > origem->size || origem->size == 0) {
        printf(notificationEnum_MOVIMENTO_INVALIDO);
        return;
    }
    if (destino->size > 0) {
        if (origem->topo->dado > destino->topo->dado) {
            printf(notificationEnum_MOVIMENTO_INVALIDO);
            return;
        }
    }
    if (origem == destino || quantidade <= 0) {
        printf(notificationEnum_MOVIMENTO_REDUNDANTE);
        return;
    }

    if (quantidade == 1) {
        dado = desempilha(origem);
        empilha(dado, destino);
        switch (_verificarDesperdicio(dado, origem->label ,destino->label, movimentos)) {
            case 2:
                return;
            case 1:
                movimentos->quantidade--;
                movimentos->passos[movimentos->quantidade] = _criarPasso(dado, movimentos->passos[movimentos->quantidade].origemLabel, destino->label);
                break;
            default:
                movimentos->passos[movimentos->quantidade] = _criarPasso(dado, origem->label, destino->label);
                break;
        }
        movimentos->quantidade++;
    } else {
        moverDisco(origem, suporte, destino, (quantidade - 1), movimentos);
        moverDisco(origem, destino, suporte, 1, movimentos);
        moverDisco(suporte, destino, origem, (quantidade - 1), movimentos);
    }
}
