#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "notification-enum.h"
#include "confirm.h"
#include "hanoi.h"

int main(int argc, char const *argv[]) {
    setlocale(LC_ALL, "Portuguese");

    // Cria uma nova instância da struct 'Hanoi'
    Hanoi *hanoi = criarHanoi();
    int final;

    // Verifica se 'hanoi' foi iniciado corretamente
    // Se não, encerra o programa para evitar erros
    if (hanoi == NULL)
        return 0;
    
    // Verifica se a organização dos discos inicial é válida
    // Se não, encerra o programa para evitar erros
    imprimirTorres(hanoi);
    if (!verificarEstruturaHanoi(hanoi)) {
        printf(notificationEnum_CONFIGURACAO_INICIAL_INVALIDA);
        return 0;
    }

    // Tenta resolver o puzzle "Torre de Hanoi" e imprime o resultado
    final = resolverHanoi(hanoi);
    imprimirFinal(hanoi, final);

    // Se o usuário desejar, imprime os movimentos que o programa usou para solucionar o puzzle
    if (final && confirm(notificationEnum_MOSTRAR_RESOLUCAO_MENSAGEM)) {
        imprimirResolucao(hanoi);
    }

    free(hanoi);
    return 0;
}