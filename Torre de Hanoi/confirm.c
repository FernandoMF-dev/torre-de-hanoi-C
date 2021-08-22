#include "confirm.h"

/*
Exibe uma mensagem pedindo uma confirmação de SIM ou NÃO
(1)- Caso o usuario responda SIM ('S' ou 'Y'), retorna 1;
(2)- Caso o usuario respona NÃO ('N'), retorna 0;
*/
int confirm(char* mensagem) {
    char enter = 0;
    while (1) {
        printf("%s (S/N): ", mensagem);
        scanf(" %c", &enter);
        if (enter == 'y' || enter == 'Y' || enter == 's' || enter == 'S')
            return 1;
        if (enter == 'n' || enter == 'N')
            return 0;
        printf(notificationEnum_CONFIRM_ENTRADA_INVALIDA);
    }
}