#ifndef IO_H
#define IO_H

#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include <stdbool.h>

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem, const char* nome_arquivo);

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem, const char* nome_arquivo);

#endif
