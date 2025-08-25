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
    HISTORICO *historico = (HISTORICO *)calloc(1, sizeof(HISTORICO));

    historico->h = pilha_criar();

    char* a = "teste";

    pilha_empilhar(historico->h, a);

    

    return historico;

    // if (historico == NULL)
    //     return NULL;
        
    // PILHA *h = pilha_criar();

    // if (h == NULL)
    // {
    //     free(historico);
    //     return NULL;
    // }

    // historico->h = h;

    // return historico;
}

// Limpa o histórico, apagando-o em seguida
void historico_apagar(HISTORICO **historico)
{
    if (*historico != NULL)
    {
        // // Remove todos os elementos da pilha (liberando memória dos procedimentos)
        // while (pilha_topo((*historico)->h) != NULL)
        // {
        //     char *procedimento = (char *)pilha_topo((*historico)->h);
        //     pilha_desempilhar((*historico)->h);
        //     free(procedimento); // Libera a string do procedimento
        // }
        
        // // Destrói a pilha
        // pilha_apagar(&((*historico)->h));
        
        // // Libera o histórico
        // free(*historico);

        pilha_apagar(&((*historico)->h));
        free(*historico);
    }
}

bool historico_inserir(HISTORICO *historico, char *procedimento)
{
    if (historico != NULL && procedimento != NULL)
    {
        // Cria uma cópia do procedimento para armazenar
        char *copia = (char *)malloc(strlen(procedimento) + 1);
        if (copia == NULL)
            return false;
            
        strcpy(copia, procedimento);
        
        // CRÍTICO: Verificar se a inserção na pilha foi bem-sucedida
        bool sucesso = pilha_empilhar(historico->h, copia);
        
        if (!sucesso) {
            // Se falhou ao empilhar, libera a cópia criada para evitar leak
            free(copia);
            return false;
        }
        
        return true;
    }

    return false;
}

bool historico_remover(HISTORICO *historico)
{
    if (historico != NULL)
    {
        char *procedimento = (char *)pilha_topo(historico->h);
        if (procedimento != NULL)
        {
            pilha_desempilhar(historico->h);
            free(procedimento); // Libera a memória do procedimento removido
            return true;
        }
    }

    return false;
}

// Função auxiliar para concatenar strings com gerenciamento de memória
char *historico_concatenar(char *destino, char *origem)
{
    if (origem == NULL)
        return destino;
        
    if (destino == NULL)
    {
        // Se destino é NULL, cria uma nova string
        char *nova = (char *)malloc(strlen(origem) + 1);
        if (nova != NULL)
            strcpy(nova, origem);
        return nova;
    }
    
    // Realoca para comportar a concatenação
    size_t tamanho_atual = strlen(destino);
    size_t tamanho_origem = strlen(origem);
    size_t tamanho_total = tamanho_atual + tamanho_origem + 1;
    
    char *novo_destino = (char *)realloc(destino, tamanho_total);
    if (novo_destino == NULL)
    {
        free(destino); // Em caso de falha, libera a memória original
        return NULL;
    }
    
    strcat(novo_destino, origem);
    return novo_destino;
}

char *historico_listar(HISTORICO *historico)
{
    if (historico == NULL)
        return NULL;

    NO *no = pilha_topo(historico->h);
    char *lista = NULL;
    char *quebra_linha = "\n";

    printf("historico_listar debug\n");

    while (no != NULL)
    {
        char *procedimento = (char *)no_get_valor(no);
        
        // Concatena o procedimento
        lista = historico_concatenar(lista, procedimento);
        if (lista == NULL)
            return NULL;
            
        printf("%s", lista);

        no = no_get_anterior(no);
        
        // Adiciona quebra de linha se não for o último elemento
        if (no != NULL)
        {
            lista = historico_concatenar(lista, quebra_linha);
            if (lista == NULL)
                return NULL;
        }
    }

    return lista;
}

// Função para calcular tamanho total necessário
size_t historico_calcular_tamanho_total(HISTORICO *historico)
{
    if (historico == NULL)
        return 0;
        
    size_t tamanho_total = 1; // Para o '\0'
    NO *no = pilha_topo(historico->h);
    int count = 0;
    
    while (no != NULL)
    {
        char *procedimento = (char *)no_get_valor(no);
        if (procedimento != NULL)
        {
            tamanho_total += strlen(procedimento);
            count++;
        }
        no = no_get_anterior(no);
    }
    
    // Adiciona espaço para quebras de linha (count - 1)
    if (count > 1)
        tamanho_total += (count - 1);
        
    return tamanho_total;
}

char *historico_concatenar2(HISTORICO *historico)
{
    if (historico == NULL)
        return NULL;

    size_t tamanho_total = historico_calcular_tamanho_total(historico);
    if (tamanho_total <= 1)
        return NULL;

    char *resultado = (char *)calloc(tamanho_total, sizeof(char));
    if (resultado == NULL)
        return NULL;

    NO *no = pilha_topo(historico->h);
    bool primeiro = true;

    printf("historico_concatenar2 debug\n");

    while (no != NULL)
    {
        char *procedimento = (char *)no_get_valor(no);
        if (procedimento != NULL)
        {
            if (!primeiro)
                strcat(resultado, "\n");
            
            strcat(resultado, procedimento);
            primeiro = false;
        }
        no = no_get_anterior(no);
    }

    return resultado;
}