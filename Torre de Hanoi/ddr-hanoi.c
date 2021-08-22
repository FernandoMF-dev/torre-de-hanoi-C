#include <stdio.h>

#include "ddr-hanoi.h"

/*
(1)- Lê retorna um inteiro que deve estar na lista de valores disponíveis de uma struct 'DiscosDisponiveisRetorno' DDR;
*/
int _validarDiscoEmLista(DiscosDisponiveisRetorno ddr) {
    int posicao;

    while (1) {
        printf("\nInserir disco: ");
        scanf(" %d", &ddr.discoSelecionado);
        posicao = findInArray(ddr.discoSelecionado, ddr.discosDisponiveis, ddr.discosDisponiveisSize);
        if (posicao < 0)
            printf("\n\tERRO: Disco não encontrado!\n");
        else
            return posicao;
    }
}


/*
(1)- Inicializa e retorna uma nova instância de uma struct 'DiscosDisponiveisRetorno'
*/
DiscosDisponiveisRetorno criarDDR(int size) {
    DiscosDisponiveisRetorno ddr;

    ddr.discosDisponiveis = (int *)malloc(size * sizeof(int));
    ddr.discosDisponiveisSize = size;
    ddr.discoSelecionado = NULL;
    for (int i = 0; i < size; i++)
        ddr.discosDisponiveis[i] = i + 1;

    return ddr;
}

/*
(1)- Lê e retorna um inteiro que deve ser igual ou maior que 0;
*/
int validarTotalDiscos() {
    int discosTotal;

    while (1) {
        printf("\nQuantidade Total de Discos: ");
        scanf(" %d", &discosTotal);
        if (discosTotal <= 0)
            printf("\n\tERRO: Entrada menor ou igual a 0 (zero)!\n");
        else
            return discosTotal;
    }
}

/*
Lê e retorna um inteiro X que deve estar num intervalo entre 0 e N;
N é a quantidade de valores disponíveis em uma struct 'DiscosDisponiveisRetorno' DDR

(1)- Retorna X;
*/
int validarQuantidadeDiscosParaRetirada(DiscosDisponiveisRetorno ddr, char *label) {
    int quantidadeDiscosParaRetirada;

    while (1) {
        printf("\nQuantidade de discos em %s (0 - %d): ", label, ddr.discosDisponiveisSize);
        scanf(" %d", &quantidadeDiscosParaRetirada);
        if (quantidadeDiscosParaRetirada > ddr.discosDisponiveisSize || quantidadeDiscosParaRetirada < 0)
            printf("\n\tERRO: Entrada inválida!\n");
        else
            return quantidadeDiscosParaRetirada;
    }
}

/*
Lê o elemento X da lista de valores disponíveis de uma struct 'DiscosDisponiveisRetorno' DDR
X é retirado da lista de valores disponíveis

(1)- Retorna X;
*/
DiscosDisponiveisRetorno encontrarDiscoEmLista(DiscosDisponiveisRetorno ddr) {
    int posicao = _validarDiscoEmLista(ddr);

    ddr.discoSelecionado = ddr.discosDisponiveis[posicao];
    ddr.discosDisponiveis = removeFromVetor(posicao, ddr.discosDisponiveis, ddr.discosDisponiveisSize);
    ddr.discosDisponiveisSize--;

    return ddr;
}