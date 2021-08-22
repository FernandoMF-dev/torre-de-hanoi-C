#ifndef ARRAY_UTILS_H_INCLUDED
#define ARRAY_UTILS_H_INCLUDED

void printArray(int *vetor, int vetorSize, char *label);

int findInArray(int agulha, int *palheiro, int palheiroSize);

int *removeFromVetor(int posicao, int *vetor, int vetorSize);

long long_pow(long base, long exp);

#endif // ARRAY_UTILS_H_INCLUDED