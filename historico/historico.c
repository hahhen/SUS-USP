#include "historico.h"
#include "../pilha/pilha.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Historico
{
    PILHA *h;
};

HISTORICO *historico_criar()
{
    HISTORICO *historico = (HISTORICO *)malloc(sizeof(HISTORICO));
    if (historico != NULL)
    {
        PILHA *h = pilha_criar();
        if (h != NULL)
        {
            historico->h = h;
        }
        else
            return NULL;
    }
    return historico;
}

/*Limpa o histórico, apagando-o em seguida (TODO)*/
void historico_apagar(HISTORICO **historico)
{
    if (*historico != NULL)
    {
        while (pilha_topo((*historico)->h) != NULL)
        {
        }
        free(*historico);
        *historico = NULL;
    }
}

bool historico_inserir(HISTORICO *historico, char *procedimento)
{
    if (historico != NULL)
    {
        return pilha_empilhar(historico->h, procedimento);
    }

    return false;
}

bool historico_remover(HISTORICO *historico)
{
    if (historico != NULL)
    {
        return pilha_desempilhar(historico->h);
    }

    return false;
}

char *historico_concatenar(char *d, char *s)
{
    size_t s_d = sizeof(d);
    size_t s_s = sizeof(s);

    size_t s_total = s_d + s_s + 1;

    char *res = (char *)malloc(s_total);

    if (res == NULL)
        return NULL;

    strcpy(res, d);
    strcat(res, s);

    return res;
}

char *historico_concatenar2(HISTORICO *historico)
{

    size_t s_total = 0;

    NO *no = pilha_topo(historico->h);

    char* br = "\n";

    // printf("historico_concatenar2: debug\n");

    while (no != NULL)
    {
        s_total += sizeof(no_get_valor(no));
        no = no_get_anterior(no);
    }

    s_total += (size_t)pilha_tamanho(historico->h);
    s_total++;

    char *res = (char *)calloc((int)s_total, s_total);

    if (res == NULL)
        return NULL;

    no = pilha_topo(historico->h);

    while (no != NULL)
    {
        strcat(res, no_get_valor(no));
        strcat(res, br);
        no = no_get_anterior(no);
    }

    return res;
}

char *historico_listar(HISTORICO *historico)
{

    NO *no = pilha_topo(historico->h);
    char *lista = "";

    // printf("historico_listar: debug\n");

    // char *br = "\n";

    // while (no != NULL)
    // {
    //     lista = historico_concatenar(lista, no_get_valor(no));
    //     // printf(": %s", lista);

    //     no = no_get_anterior(no);
    //     if (no != NULL)
    //         lista = historico_concatenar(lista, br);
    // }

    lista = historico_concatenar2(historico);

    return lista;
}