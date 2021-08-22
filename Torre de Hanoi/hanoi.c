#include <stdio.h>
#include <stdlib.h>

#include "hanoi.h"

#define TORRE_A_LABEL "Torre A"
#define TORRE_B_LABEL "Torre B"
#define TORRE_C_LABEL "Torre C"


/*
==================================================
PRIVATE
==================================================
*/

/*
Lê os valores de uma struct 'Pilha' de acordo com com os disponíveis na struct 'DiscosDisponiveisRetorno' DDR;
Cada valor lido será retirado da lista disponível em DDR;
A quantidade de valores lidos depende do valor de 'modoEscolha'.

Se 'modoEscolha' for menor que 0, todos os valores disponíveis deverão ser escolhidos;
Se 'modoEscolha' dor igual que 0, nenhum valor poderá ser escolhido;
Se 'mocoEscolha' for maior que 0, o usuário escolherá quantos valores serão escolhidos.

(1)- Retorna uma struct 'DiscosDisponiveisRetorno' sem os valores escolhidos pelo usuário.
*/
DiscosDisponiveisRetorno _montarTorre(Pilha *torre, DiscosDisponiveisRetorno ddr, int modoEscolha) {
    int posicao, discosEmpilharQuantidade;

    printf("\n\n========================= %s =========================\n", torre->label);
    if (modoEscolha == 0) {
        printf("\nQuantidade de discos em %s (0 - %d): Nenhum!\n", torre->label, ddr.discosDisponiveisSize);
        discosEmpilharQuantidade = 0;
    }
    else if (modoEscolha < 0) {
        printf("\nQuantidade de discos em %s (0 - %d): Máximo!\n", torre->label, ddr.discosDisponiveisSize);
        discosEmpilharQuantidade = ddr.discosDisponiveisSize;
    }
    else
        discosEmpilharQuantidade = validarQuantidadeDiscosParaRetirada(ddr, torre->label);

    if (discosEmpilharQuantidade > 0)
        printf("\n\tATENÇÃO: Preencha começando da base!\n");

    for (int i = 0; i < discosEmpilharQuantidade; i++) {
        printArray(ddr.discosDisponiveis, ddr.discosDisponiveisSize, "Discos Disponíveis: ");
        imprimirPilha(torre);
        ddr = encontrarDiscoEmLista(ddr);
        empilha(ddr.discoSelecionado, torre);
    }
    imprimirPilha(torre);
    printf("\n\n===========================================================\n");
    return ddr;
}

/*
Lê os valores das torres de uma struct 'Hanoi'
*/
void _montarTorres(Hanoi *hanoi) {
    DiscosDisponiveisRetorno ddr = criarDDR(hanoi->maiorDisco);

    ddr = _montarTorre(hanoi->torreA, ddr, ddr.discosDisponiveisSize);
    ddr = _montarTorre(hanoi->torreB, ddr, ddr.discosDisponiveisSize);
    ddr = _montarTorre(hanoi->torreC, ddr, (-1 * ddr.discosDisponiveisSize));

    free(ddr.discosDisponiveis);
}

/*
Verifica se os dados numa struct 'Pilha' segue as regras do puzzle "Torre de Hanoi"
(1)- Se sim, retorna 1;
(2)- Se não, retorna 0;
*/
int _verificarEstruturaHanoiIndividual(Pilha *torre) {
    No *suporte = torre->topo;
    int dado;

    while (torre->size > 0) {
        dado = suporte->dado;
        suporte = suporte->prox;
        if (suporte == NULL)
            break;
        if (dado > suporte->dado)
            return 0;
    }
    return 1;
}

/*
==================================================
CÉREBRO
==================================================
*/

/*
Procura a formação "Entrelace Duplo" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoEntrelaceDuplo(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelaceDuplo(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Procura a formação "Escada Entrelaçada" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoEscadaEntrelacada(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (hanoi->torreA->size == 0 || hanoi->torreB->size == 0 || hanoi->torreC->size == 0)
        return;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaEntrelacada(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Procura a formação "Escada com Teto" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoEscadaComTeto(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (hanoi->torreA->size == 0 || hanoi->torreB->size == 0 || hanoi->torreC->size == 0)
        return;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscadaComTeto(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Procura a formação "Entrelaçada" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoEntrelacada(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEntrelacada(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Procura a formação "Escada" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoEscada(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (hanoi->torreA->size == 0 || hanoi->torreB->size == 0 || hanoi->torreC->size == 0)
        return;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoEscada(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Procura a formação "Degrau" em uma struct 'Hanoi';
Se existir, realiza os movimentos necessários para desfazê-la.
*/
void _analizarFormacaoDegrau(Hanoi *hanoi) {
    int backupPassos = hanoi->movimentos->quantidade;

    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreA, hanoi->torreC, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreB, hanoi->torreC, hanoi->torreA, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreC, hanoi->torreA, hanoi->torreB, hanoi->movimentos);
    if (backupPassos == hanoi->movimentos->quantidade)
        formacaoDegrau(hanoi->torreC, hanoi->torreB, hanoi->torreA, hanoi->movimentos);
}

/*
Verifica se a estrutura de uma struct 'Hanoi' permite finalizar o puzzle
Se sim, conclui o puzzle "Torre de Hanoi" movendo as peças para a torre C
*/
void _analizarFinalizar(Hanoi *hanoi){
    if (hanoi->torreA->size > 0 && hanoi->torreB->size > 0 && hanoi->torreC->size > 0)
        return;
    if (verificarSequenciaTotal(hanoi) == 0)
        return;
    if (obterBase(hanoi->torreC) == hanoi->maiorDisco)
        return;

    if (obterBase(hanoi->torreA) == hanoi->maiorDisco)
        formacaoFinalizar(hanoi->torreA, hanoi->torreB, hanoi->torreC, hanoi->movimentos);
    if (obterBase(hanoi->torreB) == hanoi->maiorDisco)
        formacaoFinalizar(hanoi->torreB, hanoi->torreA, hanoi->torreC, hanoi->movimentos);
}

/*
==================================================
PUBLIC
==================================================
*/

/*
(1)- Inicializa e retorna uma nova instância de uma struct 'Hanoi'
*/
Hanoi *criarHanoi() {
    Hanoi *hanoi = (Hanoi*)malloc(sizeof(Hanoi));

    hanoi->torreA = criarPilha(TORRE_A_LABEL);
    hanoi->torreB = criarPilha(TORRE_B_LABEL);
    hanoi->torreC = criarPilha(TORRE_C_LABEL);

    if (hanoi->torreA == NULL || hanoi->torreB == NULL || hanoi->torreC == NULL)
        return NULL;

    hanoi->maiorDisco = validarTotalDiscos();
    _montarTorres(hanoi);
    hanoi->movimentos = criarMovimento(hanoi->maiorDisco);

    if (hanoi->movimentos == NULL)
        return NULL;

    return hanoi;
}

/*
Verifica se todas as torres numa struct 'Hanoi' seguem as regras do puzzle "Torre de Hanoi"
(1)- Se todas estão de acordo, retorna 1;
(2)- Se uma única delas não estiver de acordo, retorna 0.
*/
int verificarEstruturaHanoi(Hanoi *hanoi) {
    if (_verificarEstruturaHanoiIndividual(hanoi->torreA)) {
        if (_verificarEstruturaHanoiIndividual(hanoi->torreB)) {
            if (_verificarEstruturaHanoiIndividual(hanoi->torreC))
                return 1;
        }
    }
    return 0;
}

/*
Percorre todas as torres de uma struct 'Hanoi' do topo até a base verificando se seus valores estão em sequencia
    - Como sequência, entende-se, por exemplo:
        - Se TOPO tem o valor de X, então TOPO-1 tem o valor de X+1;
        - Se TOPO-1 tem o valor de X+1, então TOPO-2 tem o valor de X+2;
        - E assim por diante: (topo)[x, x+1, x+2, x+3, ..., x+n ](base).

(1)- Caso todas as torres estejam em sequência, retorna 0;
(2)- Caso uma ou mais torres não esteja em sequência, retorna 1;
*/
int verificarSequenciaTotal(Hanoi *hanoi) {
    if (verificarSequencia(hanoi->torreA) == 0) {
        if (verificarSequencia(hanoi->torreB) == 0) {
            if (verificarSequencia(hanoi->torreC) == 0)
                return 1;
        }
    }
    return 0;
}

/*
Verifica se alguma das torres numa struct 'Hanoi' possui o mesmo tamanho que o número maximo de discos
(1)- Se sim, retorna 1;
(2)- Se não, retorna 0.
*/
int verificarTamanhoFinal(Hanoi *hanoi) {
    if (hanoi->maiorDisco == hanoi->torreA->size || hanoi->maiorDisco == hanoi->torreB->size || hanoi->maiorDisco == hanoi->torreC->size)
        return 1;
    return 0;
}

/*
Verifica se o maior disco numa struct 'Hanoi' está na stuct 'Pilha' "torreC" em específico
(1)- Se sim, retorna 1;
(2)- Se não, retorna 0;
*/
int verificarBaseTorreC(Hanoi *hanoi) {
    int baseC = obterBase(hanoi->torreC);
    if (baseC != NULL ) {
        if (baseC == hanoi->maiorDisco)
            return 1;
    }
    return 0;
}

/*
Verifica se uma struct 'Hanoi' está solucionada de acordo com o puzzle "Torre de Hanoi"
(1)- Se sim, retorna 1;
(2)- Se não, retorna 0;
*/
int verificarSolucao(Hanoi *hanoi) {
    if (verificarTamanhoFinal(hanoi)) {
        if (verificarSequenciaTotal(hanoi)){
            if (verificarBaseTorreC(hanoi))
                return 1;
        }
    }
    return 0;
}

/*
Imprimi os valores de uma struct 'Hanoi'
*/
void imprimirTorres(Hanoi *hanoi) {
    printf("\n");
    imprimirPilha(hanoi->torreA);
    imprimirPilha(hanoi->torreB);
    imprimirPilha(hanoi->torreC);
    printf("\n");
}

/*
Reorganiza os valores numa struct 'Hanoi' para solucioná-la de acordo com as regras do puzzle "Torre de Hanoi"
Isso é feito seguindo as regras do puzzle "Torre de Hanoi"
Todas os movimentos feitos nessa operação são salvos na struct 'MovimentosHanoi' da struct de entrada.

(1)- Se a estrutura inicial da struct de entrada não seguir as regras do puzzle "Torre de Hanoi", retorna 0;
(2)- Se a função não conseguir reorganizar a struct de entrada, retorna 0;
(3)- Se a função tiver sucesso em seu objetivo, retorna 1;
*/
int resolverHanoi(Hanoi *hanoi) {
    int passosBackup;

    if (!verificarEstruturaHanoi(hanoi))
        return 0;

    while (verificarSolucao(hanoi) == 0 && verificarMovimentoLimite(hanoi->movimentos) == 0) {
        passosBackup = hanoi->movimentos->quantidade;

        _analizarFinalizar(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoEntrelaceDuplo(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoEscadaEntrelacada(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoEscadaComTeto(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoEntrelacada(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoEscada(hanoi);
        if (hanoi->movimentos->quantidade == passosBackup)
            _analizarFormacaoDegrau(hanoi);
    }

    return verificarSolucao(hanoi);
}

/*
Imprime uma mensagem de sucesso ou falha de acordo com o valor de FINAL
Se FINAL for igual a 0, imprime a mensagem e falha
Se FINAL for diferente de 0, imprime a mensagem de sucesso
*/
void imprimirFinal(Hanoi *hanoi, int final) {
    printf("\n\n========================= FINAL =========================\n");
    imprimirTorres(hanoi);
    if (final)
        printf(notificationEnum_FINAL_SUCESSO);
    else {
        printf(notificationEnum_FINAL_FALHA);
        printf(notificationEnum_FINAL_FALHA_MENSAGEM);
        hanoi->movimentos->quantidade = -1;
    }

    printf("\n\tNúmero de movimentos necessários: %ld", hanoi->movimentos->quantidade);
    printf("\n\n\tNúmero de discos: %d", hanoi->maiorDisco);
    printf("\n\tMelhor Solução Convencional (2^n - 1): %ld", long_pow(2, hanoi->maiorDisco) - 1);
    printf("\n\tMáximo de passos para solução (3 * 2^n): %ld", hanoi->movimentos->quantidadeMax);
    printf("\n\n=========================================================\n");
}

/*
Imprime a struct 'MovimentosHanoi' dentro de uma struct 'Hanoi'
*/
void imprimirResolucao(Hanoi *hanoi) {
        printf("\n\n========================= RESOLUÇÃO =========================\n");
        imprimirMovimentosHanoi(hanoi->movimentos);
        printf("\n\n=============================================================\n");
}
