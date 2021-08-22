#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

typedef struct No {
    int dado;
    struct No *prox;
} No;

typedef struct Pilha {
    No *topo;
    int size;
    char *label;
} Pilha;

Pilha* criarPilha(char *label);

void inicializarPilha(Pilha *pilha, char *label);

void empilha(int dado, Pilha *pilha);

int desempilha(Pilha *pilha);

void imprimirPilha(Pilha *pilha);

int obterBase(Pilha *pilha);

int verificarSequencia(Pilha *pilha);

#endif // PILHA_H_INCLUDED