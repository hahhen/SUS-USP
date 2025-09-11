#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"
#include "fila/fila.h"
#include "triagem/triagem.h"

int main()
{

    PACIENTE* paciente = paciente_criar("Arthur", 1);
    PACIENTE* paciente2 = paciente_criar("Artahur", 2);
    PACIENTE* paciente3 = paciente_criar("Arthaaur", 3);

    TRIAGEM* triagem = triagem_criar();
    triagem_inserir(triagem, paciente);
    triagem_inserir(triagem, paciente2);
    triagem_inserir(triagem, paciente3);

    printf("%s ", paciente_get_nome(triagem_remover(triagem)));
    printf("%s ", paciente_get_nome(triagem_remover(triagem)));
    printf("%s ", paciente_get_nome(triagem_remover(triagem)));

    triagem_apagar(&triagem);

    // PILHA *p = pilha_criar();
    // FILA *f = fila_criar();
    // // HISTORICO *historico = historico_criar();

    // char *a = "fulano";
    // char *b = "ciclano";

    // int *ia = (int *)malloc(sizeof(int));
    // int *ib = (int *)malloc(sizeof(int));

    // *ia = 20;
    // *ib = 32;

    // fila_inserir(f, a);
    // fila_inserir(f, b);

    // NO* na = fila_remover(f);
    // NO* nb = fila_remover(f);

    // fila_apagar(&f);

    // printf("%d", f == NULL);
    // printf("\n");

    // printf("%s\n", (char*)no_get_valor(na));
    // printf("%s\n", (char*)no_get_valor(nb));

    // PACIENTE *pa = paciente_criar(a, ia);
    // PACIENTE *pb = paciente_criar(b, ib);

    // pilha_empilhar(p, a);
    // pilha_empilhar(p, b);
    // pilha_desempilhar(p);

    // char *p1 = "teste1";
    // char *p2 = "teste2";
    // char *p3 = "teste3";

    // paciente_adicionar_procedimento(pa, p1);
    // paciente_adicionar_procedimento(pa, p2);
    // paciente_adicionar_procedimento(pa, p3);

    // // char *d = historico_listar(paciente_get_historico(pa));

    // // printf("%s", d);

    // // printf("-----------\n");

    // paciente_remover_procedimento(pa);

    // printf("%s\n", p3);

    // printf("%s", paciente_listar_procedimentos(pa));
    // printf("%s", paciente_get_nome(pa));
    // printf("%d", paciente_get_id(pa));

    // pilha_apagar(&p);

    // historico_inserir(historico, a);
    // historico_inserir(historico, b);
    // historico_inserir(historico, b);

    // historico_remover(historico);

    // printf("%s", no_get_valor(pilha_topo(p)));
    // char *d = historico_listar(historico);
    // printf("%s", d);

    return 0;
}