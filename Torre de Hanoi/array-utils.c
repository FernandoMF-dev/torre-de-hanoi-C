#include "array-utils.h"

/*
Imprimi os valores de um array de inteiros.
*/
void printArray(int *vetor, int vetorSize, char *prefixo) {
    printf("\n%s[ ", prefixo);
    for (int i = 0; i < vetorSize; i++)
        printf("%d ", vetor[i]);
    printf("]");
}

/*
Percorre um array PALHEIRO em busca do valor AGULHA
(1)- Retorna o índice de PALHEIRO da primeira instância de AGULHA no vetor
(2)- Caso não exista uma única instância de AGULHA em PALHEIRO, retorna -1
*/
int findInArray(int agulha, int *palheiro, int palheiroLength) {
    for (int i = 0; i < palheiroLength; i++) {
        if (agulha == palheiro[i])
            return i;
    }
    return -1;
}

/*
(1)- Recebe um array e retorna uma cópia desse array sem a posição INDEX
*/
int *removeFromVetor(int index, int *array, int arrayLength) {
    int *saida = (int *)malloc((arrayLength - 1) * sizeof(int));
    int i = 0, j = 0;
    int removeu = 0;

    for (i = 0; i < arrayLength; i++) {
        if (index == i && !removeu)
            removeu = 1;
        else {
            saida[j] = array[i];
            j++;
        }
    }
    return saida;
}

/*
(1)- Renorna a potência de uma potenciação de LONG's
*/
long long_pow(long base, long exp) {
    long result = 1;

    while (exp) {
        if (exp % 2)
            result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}
