
#include "./lista_pacientes.h"
#include "../lista/lista.h"
#include "../no/no.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct lista_pacientes_
{
    LISTA *l;
};

LISTA_PACIENTES *lista_pacientes_criar()
{
    LISTA_PACIENTES *lista = (LISTA_PACIENTES *)malloc(sizeof(LISTA_PACIENTES));
    if (lista != NULL)
    {
        lista->l = lista_criar();
        if (lista->l == NULL)
        {
            free(lista);
            return NULL;
        }
    }
    return lista;
}

bool lista_pacientes_inserir(LISTA_PACIENTES *lista, PACIENTE* paciente)
{
    if (lista != NULL && lista->l != NULL && paciente != NULL)
    {
        return lista_inserir(lista->l, paciente);
    }
    return false;
}

bool lista_pacientes_busca_id_e_adiciona_procedimento(LISTA_PACIENTES *lista, int id, char* procedimento){
    PACIENTE* p = lista_pacientes_busca(lista, id);

    if(p == NULL) return false;

    return paciente_adicionar_procedimento(p, procedimento);
}

bool lista_pacientes_remover_procedimento(LISTA_PACIENTES *lista, int id){
    PACIENTE* p = lista_pacientes_busca(lista, id);

    if(p == NULL) return false;

    return paciente_remover_procedimento(p);
}

bool lista_pacientes_remover(LISTA_PACIENTES *lista, void *chave)
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_remover(lista->l, chave, paciente_get_id, paciente_remover_ponteiro);
    }
    return false;
}

bool comparar_id_paciente(void* id1, void* id2){
    return (*(int*)id1) == (*(int*)id2);
}

void *lista_pacientes_busca(LISTA_PACIENTES *lista, void *chave)
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_busca(lista->l, chave, paciente_get_id);
    }
    return NULL;
}

void lista_pacientes_imprimir(LISTA_PACIENTES *lista)
{
    if (lista != NULL && lista->l != NULL)
    {
        printf("Lista de Pacientes:\n");
        lista_imprimir(lista->l, paciente_get_nome);
    }
}

int lista_pacientes_tamanho(LISTA_PACIENTES *lista)
{
    if (lista != NULL && lista->l != NULL)
    {
        return lista_tamanho(lista->l);
    }
    return -1;
}

NO *lista_pacientes_get_inicio(LISTA_PACIENTES *lista) {
    if (lista != NULL && lista->l != NULL) {
        return lista_get_no_head(lista->l);
    }
    return NULL;
}

bool lista_pacientes_apagar(LISTA_PACIENTES **lista)
{
    if (lista != NULL && *lista != NULL)
    {
        if ((*lista)->l != NULL)
        {
            lista_apagar(&((*lista)->l), paciente_remover);
        }
        free(*lista);
        *lista = NULL;
        return true;
    }
    return false;
}

NO* lista_pacientes_get_no_head(LISTA_PACIENTES* lista){
    if(lista != NULL && lista->l != NULL){
        return lista_get_no_head(lista->l);
    }
    return NULL;
}