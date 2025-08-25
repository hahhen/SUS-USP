#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"

int main()
{

    // PILHA *p = pilha_criar();
    // HISTORICO *historico = historico_criar();

    char *a = "a";
    char *b = "b";

    int ia = 1;
    int ib = 2;

    // HISTORICO *h = historico_criar();

    PACIENTE* pa = paciente_criar(a, ia);

    // PACIENTE* pb = paciente_criar(b, ib);   
    
    // paciente_remover(&pb);

    // historico_apagar(&h);

    // paciente_adicionar_procedimento(pa, a); causando leak

    paciente_remover(&pa);

    // historico_inserir(historico, b);
    // historico_inserir(historico, b);

    // historico_remover(historico);

    // printf("%s", no_get_valor(pilha_topo(p)));
    // char *d = historico_listar(historico);
    // printf("%s", d);

    return 0;
}