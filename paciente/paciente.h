#ifndef PACIENTE_H
#define PACIENTE_H

#include <stdbool.h>

#include "../historico/historico.h"

typedef struct Paciente PACIENTE;

PACIENTE* paciente_criar(char *nome, int id);

char *paciente_get_nome(PACIENTE *paciente);

int paciente_get_id(PACIENTE *paciente);

HISTORICO *paciente_get_historico(PACIENTE *paciente);

bool paciente_adicionar_procedimento(PACIENTE *paciente, char *procedimento);

bool paciente_remover_procedimento(PACIENTE *paciente);

char *paciente_listar_procedimentos(PACIENTE *paciente);

void paciente_remover(PACIENTE **paciente);

bool comparar_pacientes(void *p1, void *p2);

#endif