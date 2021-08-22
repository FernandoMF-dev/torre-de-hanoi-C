#ifndef FORMACAO_HANOI_H_INCLUDED
#define FORMACAO_HANOI_H_INCLUDED

#include "pilha.h"
#include "movimento-hanoi.h"

void formacaoFinalizar(Pilha *principal, Pilha *secundaria, Pilha *torreC, MovimentosHanoi *movimentos);

void formacaoEntrelaceDuplo(Pilha *superior, Pilha *inferior, Pilha *suporte, MovimentosHanoi *movimentos);

void formacaoEscadaEntrelacada(Pilha *principal, Pilha *maior, Pilha *menor, MovimentosHanoi *movimentos);

void formacaoEscadaComTeto(Pilha *principal, Pilha *menor, Pilha *maior , MovimentosHanoi *movimentos);

void formacaoEntrelacada(Pilha *maior, Pilha *menor, Pilha *suporte, MovimentosHanoi *movimentos);

void formacaoEscada(Pilha *base, Pilha *meio, Pilha *cume, MovimentosHanoi *movimentos);

void formacaoDegrau(Pilha *base, Pilha *topo, Pilha *suporte, MovimentosHanoi *movimentos);

#endif // FORMACAO_HANOI_H_INCLUDED