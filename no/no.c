#include "no.h"
#include <stdio.h>
#include <stdlib.h>

struct No {
    void* valor;
    NO* anterior;
};

NO* no_criar(void* valor, NO* anterior) {
    NO *no = (NO*) malloc(sizeof(NO));
    if (no != NULL) {
        no->valor = valor;
        no->anterior = anterior;
    }
    return no;
}

NO* no_get_anterior(NO* no){
    if(no != NULL){
        return no->anterior;
    }
    return NULL;
}

void no_remover(NO **no) {
    if (*no != NULL) {
        free((*no)->valor);
        free(*no);
        *no = NULL;
    }
}