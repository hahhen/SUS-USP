#include "pilha.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>

struct pilha
{
    int tamanho;
    NO *topo;
};

PILHA *pilha_criar()
{

    PILHA *p = (PILHA *)malloc(sizeof(PILHA));

    if (p != NULL)
    {
        p->tamanho = 0;
        p->topo = NULL;
    }

    return p;
}

bool pilha_vazia(PILHA *p)
{
    if (p != NULL)
    {
        return p->tamanho == 0;
    }

    return false;
}

bool pilha_cheia(PILHA *p)
{
    if (p != NULL)
    {

        NO *tentativa = no_criar(NULL, NULL);

        if (tentativa == NULL)
        {
            return true;
        }

        free(tentativa);
        return false;
    }

    return false;
}

int pilha_tamanho(PILHA *p)
{

    if (p != NULL)
    {
        return p->tamanho;
    }

    return -1;
}

bool pilha_empilhar(PILHA *p, void *valor)
{

    NO *no = no_criar(valor, NULL);

    if (no == NULL)
        return false;

    if ((p != NULL) && (!pilha_cheia(p)))
    {

        no_set_anterior(no, p->topo);

        p->topo = no;

        p->tamanho++;

        return true;
    }

    return false;
}

void *pilha_desempilhar(PILHA *p)
{
    NO *no;
    if ((p != NULL) && (!pilha_vazia(p)))
    {

        no = pilha_topo(p);

        void *no_valor = no_get_valor(no);

        p->topo = no_get_anterior(no);

        no_remover(&no);

        p->tamanho--;

        return no_valor;
    }

    return NULL;
}

NO *pilha_topo(PILHA *p)
{
    if (p != NULL && p->tamanho > 0)
    {
        return p->topo;
    }

    return NULL;
}

void pilha_apagar(PILHA **p)
{
    if(pilha_vazia(*p)){
        free(*p);
        *p = NULL;
        return;
    }

    if (*p == NULL)
        return;

    NO *no_temp = pilha_topo(*p);

    while ((*p)->topo != NULL)
    {
        no_temp = (*p)->topo;
        // printf("valor_no: %s ", no_get_valor(no_temp));
        (*p)->topo = no_get_anterior(no_temp);
        no_remover(&no_temp);
        no_set_anterior(no_temp, NULL);
        free(no_temp);
        no_temp = NULL;
    }

    free(*p);
    *p = NULL;
}
