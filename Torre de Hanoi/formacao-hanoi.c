#include <stdio.h>
#include <stdlib.h>

#include "formacao-hanoi.h"

/*
Conclui o puzzle "Torre de Hanoi" movendo as peças para a torre C
*/
void formacaoFinalizar(Pilha *principal, Pilha *secundaria, Pilha *torreC, MovimentosHanoi *movimentos) {
    if (principal->size > 0 && secundaria->size == 0 && torreC->size ==0) {
        moverDisco(principal, torreC, secundaria, principal->size, movimentos);
        return;
    }

    if (principal->size == 1) {
        if (torreC->size > 0)
            moverDisco(torreC, secundaria, principal, torreC->size, movimentos);
        moverDisco(principal, torreC, secundaria, principal->size, movimentos);
        moverDisco(secundaria, torreC, principal, secundaria->size, movimentos);
        return;
    }

    if (secundaria->size > 0)
        moverDisco(secundaria, principal, torreC, secundaria->size, movimentos);
    else
        moverDisco(torreC, principal, secundaria, torreC->size, movimentos);
    moverDisco(principal, torreC, secundaria, principal->size, movimentos);
}

/*
########## Formação "Entrelace Duplo" ##########

[ cume | base ]

Superior:   A[ 1 2 | 4 ]
Inferior:   B[ 3 | 5 ]
Suporte:    C[ ]

1º O cume de 'A' pode ser movido para 'B';
2º O cume de 'A' pode ser movido para 'C';
3º O cume de 'B' tem altura igual a 1;
4º O cume de 'B' cabe entre o cume 'A' e a base de 'A'
5º O cume de 'A' tem altura de 1;
6º O cume de 'A' cabe entre o cume 'B' e a base de 'B'
*/
void formacaoEntrelaceDuplo(Pilha *superior, Pilha *inferior, Pilha *suporte, MovimentosHanoi *movimentos) {
    int superiorAltura = verificarSequencia(superior);
    int inferiorAltura = verificarSequencia(inferior);
    No *superiorBase = superior->topo;

    if (superiorAltura == 0 || inferiorAltura != 1)
        return;
    for (int i = 0; i < superiorAltura; i++)
        superiorBase = superiorBase->prox;
    if (suporte->size > 0) {
        if (inferior->topo->dado > suporte->topo->dado)
            return;
    }
    if (superior->topo->dado + superiorAltura != inferior->topo->dado || inferior->topo->dado != superiorBase->dado - 1 || superiorBase->dado + 1 != inferior->topo->prox->dado)
        return;

    moverDisco(inferior, suporte, superior, inferiorAltura, movimentos);
    moverDisco(superior, suporte, inferior, superiorAltura, movimentos);
    moverDisco(superior, inferior, suporte, inferiorAltura, movimentos);
}

/*
########## Formação "Escada Entrelaçada" ##########

[ cume | base ]

Principal:  A[ 1 2 | 4 ]
Menor:      B[ 3 ]
Maior:      C[ 5 ]

1º Nenhuma torre está vazia
2º O cume de 'A' pode ser movido para 'B'
3º A base de 'A' tem altura igual a 1;
4º 'B' cabe entre o cume de 'A' e a base de 'A'
5º A base de 'A' pode ser movida para 'C'
*/
void formacaoEscadaEntrelacada(Pilha *principal, Pilha *maior, Pilha *menor, MovimentosHanoi *movimentos) {
    int principalAltura = verificarSequencia(principal);
    No *suporte = principal->topo;

    if (principal->size <= 1 || principalAltura == 0)
        return;

    for (int i = 0; i < principalAltura; i++)
        suporte = suporte->prox;

    if (principal->topo->dado + principalAltura != menor->topo->dado
        || menor->topo->dado + 1 != suporte->dado
        || suporte->dado + 1 != maior->topo->dado)
            return;

    moverDisco(principal, menor, maior, principalAltura, movimentos);
    moverDisco(principal, maior, menor, 1, movimentos);
}

/*
########## Formação "Escada com Teto" ##########

[ cume | base ]

Principal:  A[ 1 2 | 5 ]
Menor:      B[ 3 ]
Maior:      C[ 4 ]

1º Nenhuma torre está vazia
2º O cume de 'A' pode ser movido para 'B'
3º 'B' pode ser movido para 'C'
4º 'C' tem altura igual a 1;
5º 'C' pode ser movido para a base de 'A'
*/
void formacaoEscadaComTeto(Pilha *principal, Pilha *menor, Pilha *maior , MovimentosHanoi *movimentos) {
    int principalAltura = verificarSequencia(principal);
    No *suporte = principal->topo;

    if (principal->size <= 1 || principalAltura == 0)
        return;

    for (int i = 0; i < principalAltura; i++)
        suporte = suporte->prox;

    if (principal->topo->dado + principalAltura != menor->topo->dado || menor->topo->dado + 1 != maior->topo->dado || maior->topo->dado + 1 != suporte->dado)
        return;

    moverDisco(principal, menor, maior, principalAltura, movimentos);
    moverDisco(maior, principal, menor, 1, movimentos);
}

/*
########## Formação "Entrelaçada" ##########

[ cume | base ]

Primaria:   A[ 1 2 | 5 ]
Secundaria: B[ 3 4 ]
Suporte:    C[ ]

1º O cume de 'A' pode ser movida para 'B'
2º O cume de 'A' pode ser movida para 'C'
3º 'B' cabe entre o cume de 'A' e a base de 'A'
*/
void formacaoEntrelacada(Pilha *primaria, Pilha *secundaria, Pilha *suporte, MovimentosHanoi *movimentos) {
    int primariaAltura = verificarSequencia(primaria);
    int secundariaAltura = verificarSequencia(secundaria);
    No *auxiliar = primaria->topo;

    if (primariaAltura == 0 || secundaria->size == 0)
        return;

    if (secundariaAltura == 0)
        secundariaAltura = secundaria->size;

    if (suporte->size > 0) {
        if (primaria->topo->dado + primariaAltura >= suporte->topo->dado)
            return;
    }

    for (int count = 0; count < primariaAltura; count++)
        auxiliar = auxiliar->prox;

    if (primaria->topo->dado + primariaAltura != secundaria->topo->dado || secundaria->topo->dado + secundariaAltura != auxiliar->dado)
        return;

    if (secundariaAltura == 1)
        moverDisco(primaria, suporte, secundaria, primariaAltura, movimentos);
    else
        moverDisco(primaria, secundaria, suporte, primariaAltura, movimentos);
}

/*
########## Formação "Escada" ##########

Superior:       A[ 1 2 ]
Intermediaria:  B[ 3 4 5 ]
Inferior:       C[ 6 ]

1º Nenhuma torre está vazia
2º 'A' pode ser movido para 'B'
3º 'B' pode ser movido para 'C'
*/
void formacaoEscada(Pilha *inferior, Pilha *intermediaria, Pilha *superior, MovimentosHanoi *movimentos) {
    int superiorAltura = verificarSequencia(superior);
    int intermediariaAltura = verificarSequencia(intermediaria);

    if (superiorAltura == 0)
        superiorAltura = superior->size;
    if (intermediariaAltura == 0)
        intermediariaAltura = intermediaria->size;

    if (superior->topo->dado + superiorAltura != intermediaria->topo->dado || intermediaria->topo->dado + intermediariaAltura != inferior->topo->dado)
        return;

    if (intermediariaAltura == 1)
        moverDisco(intermediaria, inferior, superior, intermediariaAltura, movimentos);
    else
        moverDisco(superior, intermediaria, inferior, superiorAltura, movimentos);
}

/*
########## Formação "Degrau" ##########

Superior:   A[ 1 2 3 4 ]
Inferior:   B[ 5 6 ]
Suporte:    C[ ]

1º 'A' pode ser movido para 'B'
2º 'A' pode ser movido para 'C' se a altura de 'A' for maior que 1
*/
void formacaoDegrau(Pilha *inferior, Pilha *superior, Pilha *suporte, MovimentosHanoi *movimentos) {
    int superiorAltura = verificarSequencia(superior);

    if (inferior->size == 0 || superior->size == 0)
        return;

    if (superiorAltura == 0)
        superiorAltura = superior->size;

    if (superiorAltura > 1 && suporte->size > 0) {
        if (superior->topo->dado + superiorAltura >= suporte->topo->dado)
            return;
    }

    if (superior->topo->dado + superiorAltura != inferior->topo->dado)
        return;

    moverDisco(superior, inferior, suporte, superiorAltura, movimentos);
}
