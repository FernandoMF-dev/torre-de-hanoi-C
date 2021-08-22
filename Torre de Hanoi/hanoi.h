#ifndef HANOI_H_INCLUDED
#define HANOI_H_INCLUDED

#include "pilha.h"
#include "ddr-hanoi.h"
#include "movimento-hanoi.h"
#include "notification-enum.h"
#include "formacao-hanoi.h"

typedef struct Hanoi {
    Pilha *torreA;
    Pilha *torreB;
    Pilha *torreC;
    MovimentosHanoi *movimentos;
    int maiorDisco;
} Hanoi;

int verificarEstruturaHanoi(Hanoi *hanoi);

int verificarSequenciaTotal(Hanoi *hanoi);

int verificarTamanhoFinal(Hanoi *hanoi);

int verificarSolucao(Hanoi *hanoi);

void imprimirTorres(Hanoi *hanoi);

Hanoi *criarHanoi();

int resolverHanoi(Hanoi *hanoi);

void imprimirFinal(Hanoi *hanoi, int final);

void imprimirResolucao(Hanoi *hanoi);

int verificarBaseTorreC(Hanoi *hanoi);

#endif // HANOI_H_INCLUDED