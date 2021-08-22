#ifndef MOVIMENTO_HANOI_H_INCLUDED
#define MOVIMENTO_HANOI_H_INCLUDED

#include "notification-enum.h"
#include "pilha.h"

typedef struct PassoHanoi {
    int disco;
    char *origemLabel;
    char *destinoLabel;
} PassoHanoi;

typedef struct MovimentosHanoi {
    long quantidadeMax;
    long quantidade;
    PassoHanoi *passos;
} MovimentosHanoi;

MovimentosHanoi* criarMovimento(int maiorDisco);

void imprimirMovimentosHanoi(MovimentosHanoi *movimentos);

int verificarMovimentoLimite(MovimentosHanoi *movimentos);

void moverDisco(Pilha *origem, Pilha *destino, Pilha *suporte, int quantidade, MovimentosHanoi *movimentos);

#endif // MOVIMENTO_HANOI_H_INCLUDED