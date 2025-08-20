#include <stdio.h>
#include "pilha/pilha.h"

int main(){

    PILHA* p = pilha_criar();

    char* a = "1";
    char* b = "2";

    pilha_empilhar(p, a);

    pilha_empilhar(p, b);

    pilha_desempilhar(p);

    printf("%s", no_get_valor(pilha_topo(p)));

    return 0;
}