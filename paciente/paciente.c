#include "paciente.h"
#include "../historico/historico.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Paciente
{
    char *nome;
    int *id;
    HISTORICO *historico;
};

PACIENTE *paciente_criar(char *nome, int *id)
{
    PACIENTE *paciente = (PACIENTE *)malloc(sizeof(PACIENTE));
    
    if(paciente == NULL) return NULL;

    HISTORICO *historico = historico_criar();

    if(historico == NULL){
        free(paciente);
        paciente = NULL;
        return NULL;
    }

    paciente->nome = nome;
    paciente->id = id;
    paciente->historico = historico;

    return paciente;
    return NULL;
}

char *paciente_get_nome(PACIENTE *paciente)
{
    if (paciente == NULL)
        return NULL;

    return paciente->nome;
}

int *paciente_get_id(PACIENTE *paciente)
{
    if (paciente == NULL)
        return NULL;

    return paciente->id;
}

bool paciente_adicionar_procedimento(PACIENTE *paciente, char *procedimento)
{
    if (paciente == NULL || strlen(procedimento) == 0 || paciente->historico == NULL)
        return false;

    historico_inserir(paciente->historico, procedimento);
    return true;
}

bool paciente_remover_procedimento(PACIENTE *paciente)
{
    if (paciente == NULL || paciente->historico == NULL)
        return false;

    return historico_remover(paciente->historico);
}

char *paciente_listar_procedimentos(PACIENTE *paciente)
{
    if (paciente == NULL || paciente->historico == NULL)
        return NULL;

    // printf("paciente_listar_procedimentos: debug\n");
    char *res = historico_listar(paciente->historico);

    return res;
}

void paciente_remover(PACIENTE **paciente)
{
    if (*paciente == NULL)
        return;

    historico_apagar(&(*paciente)->historico);
    free((*paciente)->nome);
    free((*paciente)->id);
    free(*paciente);
    *paciente = NULL;
}
