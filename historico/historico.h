#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdbool.h>

typedef struct Historico HISTORICO;

HISTORICO* historico_criar();

void historico_apagar(HISTORICO **historico);

bool historico_inserir(HISTORICO* historico, char* procedimento);

bool historico_remover(HISTORICO* historico);

char* historico_listar(HISTORICO* historico);

#endif