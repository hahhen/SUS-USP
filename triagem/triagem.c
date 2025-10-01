#include "../fila/fila.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../paciente/paciente.h"
#define TAM_MAX 10000

typedef struct triagem
{
	FILA *fila;
} TRIAGEM;

TRIAGEM *triagem_criar()
{
	TRIAGEM *triagem = malloc(sizeof(TRIAGEM));
	if (triagem != NULL)
	{
		FILA *fila = fila_criar();
		if (fila != NULL)
		{
			triagem->fila = fila;
			return triagem;
		}
	}

	return NULL;
}

int triagem_tamanho(TRIAGEM *triagem)
{
	if (triagem != NULL)
		return fila_tamanho(triagem->fila);
	return -1;
}

bool triagem_cheia(TRIAGEM *triagem)
{
	if (triagem != NULL)
		return triagem_tamanho(triagem) >= TAM_MAX;
	return false;
}

void triagem_apagar(TRIAGEM **triagem)
{
	if ((*triagem) != NULL)
	{
		fila_apagar(&(*triagem)->fila);
		free(*triagem);
		*triagem = NULL;
	}
}

bool triagem_vazia(TRIAGEM *triagem)
{
	if (triagem != NULL)
		return fila_vazia(triagem->fila);
	return false;
}

PACIENTE *triagem_remover(TRIAGEM *triagem)
{
	if (triagem != NULL && !triagem_vazia(triagem))
	{
		PACIENTE *paciente = fila_remover(triagem->fila);
		return paciente;
	}
	return NULL;
}

bool triagem_inserir(TRIAGEM *triagem, PACIENTE *paciente)
{
	if (triagem != NULL && !triagem_cheia(triagem) && paciente != NULL)
		return fila_inserir(triagem->fila, paciente);
	return false;
}

NO* triagem_get_inicio(TRIAGEM *triagem) {
    if (triagem != NULL && triagem->fila != NULL) {
        return fila_get_inicio(triagem->fila);
    }
    return NULL;
}