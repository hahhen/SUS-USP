#include "IO.h"
#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include "../paciente/paciente.h"
#include "../historico/historico.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem, const char* nome_arquivo){
    if(!lista || !triagem) 
        return false;
    
    NO *no; // Variável auxiliar 


    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista)
        return false;

    no = LISTA_remover_inicio(lista);
    int chave;
    while(no != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        chave = no_get_chave(no);
        fwrnoe(&chave, sizeof(int), 1, fp_lista);
        // Apaga o noem removido
        no_apagar(&no);
        // Atualiza a variável auxiliar
        no = LISTA_remover_inicio(lista);
    }
    // Libera memória
    LISTA_apagar(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os noens da triagem

    FILE *fp_triagem = fopen("triagem_noens.bin", "wb");
    if(!fp_triagem)
        return false;

    no = FILA_remover(triagem);
    while(no != NULL) { // Se mantém no while enquanto a triagem não estiver vazia
        // Escreve a chave no arquivo
        chave = no_get_chave(no);
        fwrnoe(&chave, sizeof(int), 1, fp_triagem);
        // Apaga o nó removido
        no_remover(&no);
        // Atualiza a variável auxiliar
        no = FILA_remover(triagem);
    }
    // Libera memória
    FILA_apagar(&triagem);
    fclose(fp_triagem); fp_triagem = NULL;

    return true;
}

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem, const char* nome_arquivo){
    if(!*lista || !*triagem) 
        return false;

    int chave; // Variável auxiliar

    // Carregando os noens do arquivo na lista

    FILE *fp_lista = fopen("lista_noens.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_lista) == 1) {
        no *no = no_criar(chave);
        LISTA_inserir(*lista, no);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os noens do arquivo na triagem

    FILE *fp_triagem = fopen("triagem_noens.bin", "rb");
    if(!fp_triagem)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&chave, sizeof(int), 1, fp_triagem) == 1) {
        no *no = no_criar(chave);
        FILA_inserir(*triagem, no);
    }
    fclose(fp_triagem); // Libera memória

    return true;
}