#ifndef DDR_HANOI_H_INCLUDED
#define DDR_HANOI_H_INCLUDED

#include "array-utils.h"

typedef struct DiscosDisponiveisRetorno {
    int *discosDisponiveis;
    int discosDisponiveisSize;
    int discoSelecionado;
} DiscosDisponiveisRetorno;

DiscosDisponiveisRetorno criarDDR(int size);

int validarTotalDiscos();

int validarQuantidadeDiscosParaRetirada(DiscosDisponiveisRetorno ddr, char *label);

DiscosDisponiveisRetorno encontrarDiscoEmLista(DiscosDisponiveisRetorno ddr);

#endif // DDR_HANOI_H_INCLUDED