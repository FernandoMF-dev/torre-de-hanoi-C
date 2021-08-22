#include "notification-enum.h"

#define CONFIRM_ENTRADA_INVALIDA "\n\tERRO: Entrada INVÁLIDA! Usar apenas: S/Y - Sim; N - Não\n"
#define CONFIGURACAO_INICIAL_INVALIDA "\n\tERRO: Configuração inicial INVÁLIDA!\n\n"
#define MOVIMENTO_INVALIDO "\n\tERRO: Movimento inválido!"
#define MOVIMENTO_REDUNDANTE "\n\tERRO: Movimento redundante!"
#define FINAL_SUCESSO "\n\t!!! PUZZLE SOLUCIONADO COM SUCESSO !!!"
#define FINAL_FALHA "\n\t!!! PUZZLE NÃO SOLUCIONADO !!!"
#define FINAL_FALHA_MENSAGEM "\n\tO programa não pôde solucionar o puzzle com menos movimentos que a quantidade máxima disponível!"
#define MOSTRAR_RESOLUCAO_MENSAGEM "\nMostrar passo-a-passo para a resolução"

char* notificationEnum_CONFIRM_ENTRADA_INVALIDA = CONFIRM_ENTRADA_INVALIDA;
char* notificationEnum_CONFIGURACAO_INICIAL_INVALIDA = CONFIGURACAO_INICIAL_INVALIDA;
char* notificationEnum_MOVIMENTO_INVALIDO = MOVIMENTO_INVALIDO;
char* notificationEnum_MOVIMENTO_REDUNDANTE = MOVIMENTO_REDUNDANTE;
char* notificationEnum_FINAL_SUCESSO = FINAL_SUCESSO;
char* notificationEnum_FINAL_FALHA = FINAL_FALHA;
char* notificationEnum_FINAL_FALHA_MENSAGEM = FINAL_FALHA_MENSAGEM;
char* notificationEnum_MOSTRAR_RESOLUCAO_MENSAGEM = MOSTRAR_RESOLUCAO_MENSAGEM;