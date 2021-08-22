#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

#define ERRO_ALOCACAO_PILHA "\n\tERRO: Erro de alocação de Pilha!\n"
#define ERRO_ALOCACAO_NO "\n\tERRO: Erro de alocação de Nó!\n"
#define ERRO_PILHA_VAZIA "\n\tERRO: Pilha Vazia!\n"

/*
(1)- Retorna a nova instância de uma struct 'Pilha' já com os campos inicializados
*/
Pilha* criarPilha(char *label) {
    Pilha *novaPilha = (Pilha *)malloc(sizeof(Pilha));

    if (novaPilha == NULL) {
        printf(ERRO_ALOCACAO_PILHA);
        return NULL;
    }
    inicializarPilha(novaPilha, label);

    return novaPilha;
}

/*
Configura uma struct 'Pilha' com valores iniciais
*/
void inicializarPilha(Pilha *pilha, char *label) {
    pilha->topo = NULL;
    pilha->size = 0;
    pilha->label = label;
}

/*
(1)- Adiciona um valor no topo da pilha
*/
void empilha(int dado, Pilha *pilha) {
    No *ptr = (No *)malloc(sizeof(No));

    if (ptr == NULL)
        printf(ERRO_ALOCACAO_NO);
    else {
        ptr->dado = dado;
        ptr->prox = pilha->topo;
        pilha->topo = ptr;
        pilha->size++;
    }
}

/*
(1)- Remove e retorna o valor do topo da pilha
(2)- Caso a pilha esteja vazia, retorna NULL
*/
int desempilha(Pilha *pilha) {
    No *ptr = pilha->topo;
    int backup;

    if (ptr == NULL) {
        printf(ERRO_PILHA_VAZIA);
        return NULL;
    } else {
        pilha->topo = ptr->prox;
        ptr->prox = NULL;
        backup = ptr->dado;
        free(ptr);
        pilha->size--;
        return (backup);
    }
}

/*
Imprimi os valores de uma struct 'Pilha'
*/
void imprimirPilha(Pilha *pilha) {
    No *ptr = pilha->topo;

    printf("\n%s[ ", pilha->label);
    while (ptr != NULL) {
        printf("%d", ptr->dado);
        if (ptr->prox != NULL)
            printf(" | ");
        ptr = ptr->prox;
    }
    printf(" ]\n");
}

/*
(1)- Retorna o valor na base de uma pilha sem alterá-la
(2)- Caso a pilha esteja vazia, retorna NULL
*/
int obterBase(Pilha *pilha) {
    No *suporte = pilha->topo;
    int dado = NULL;
    
    while (suporte != NULL) {
        dado = suporte->dado;
        suporte = suporte->prox;
    }

    return dado;
}

/*
Percorre uma struct 'Pilha' do topo até a base verificando se seus valores estão em sequencia
    - Como sequência, entende-se, por exemplo:
        - Se TOPO tem o valor de X, então TOPO-1 tem o valor de X+1;
        - Se TOPO-1 tem o valor de X+1, então TOPO-2 tem o valor de X+2;
        - E assim por diante: (topo)[x, x+1, x+2, x+3, ..., x+n ](base).

(1)- Caso a struct 'Pilha' esteja vazia ou esta totalmente em sequência, retorna 0;
(2)- Caso a struct 'Pilha' não cumpra o cenário (1), retorna um inteiro N maior que 0;
    (2.1)- N sendo o número de elementos que encontram-se em sequência antes da quebra do padrão
        (2.1.1)- Sempre contando a partir do topo para a base;
*/
int verificarSequencia(Pilha *pilha) {
    No *suporte = pilha->topo;
    int dado, saida = 0;

    while (pilha->size != 0) {
        saida++;
        dado = suporte->dado;
        suporte = suporte->prox;
        if (suporte == NULL)
            return 0;
        if (dado != (suporte->dado - 1))
            break;
    }

    return saida;
}