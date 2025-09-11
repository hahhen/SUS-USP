#ifndef _LISTA_H
#define _LISTA_H

    #include "../no/no.h"
    #include <stdbool.h>

    typedef struct lista LISTA;

    LISTA *lista_criar(void);
    bool lista_apagar(LISTA **lista);
    bool lista_inserir(LISTA *lista, void *valor);
    NO* lista_remover(LISTA *lista, void *valor);
    NO* lista_buscar(LISTA *lista, void *valor);
    bool lista_vazia(LISTA *lista);
    bool lista_cheia(LISTA *lista);
    int lista_tamanho(LISTA *lista);

#endif