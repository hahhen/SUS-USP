#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"
#include "fila/fila.h"
#include "lista/lista.h"

int main()
{

    PILHA *p = pilha_criar();
    FILA *f = fila_criar();
    LISTA *l = lista_criar();

    char* teste = "teste";
    char* teste2 = "teste2";
    char* teste3 = "teste3";

    PACIENTE* paciente = paciente_criar(teste, 20);
    PACIENTE* paciente2 = paciente_criar(teste2, 32);

    lista_inserir(l, paciente);
    lista_inserir(l, paciente2);

    lista_remover(l, 32, paciente_get_id);

    lista_busca(l, teste2, paciente_get_nome, strcmp);

    lista_imprimir(l, paciente_get_nome);

    // HISTORICO *historico = historico_criar();

    char *a = "fulano";
    char *b = "ciclano";

    int *ia = (int *)malloc(sizeof(int));
    int *ib = (int *)malloc(sizeof(int));

    *ia = 20;
    *ib = 32;

    fila_inserir(f, a);
    fila_inserir(f, b);

    NO *na = fila_remover(f);
    NO *nb = fila_remover(f);

    fila_apagar(&f);

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