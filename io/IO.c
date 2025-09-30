#include "IO.h"
#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include "../paciente/paciente.h"
#include "../no/no.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *fila){
    if(!lista || !TRIAGEM) 
        return false;
    
    NO *no; // Variável auxiliar 

    // Salvando os pacientes da lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if(!fp_lista)
        return false;

    no = lista_pacientes_get_no_head(lista);
    PACIENTE* p;
    while(no != NULL) { // Se mantém no while enquanto a lista não estiver vazia
        // Escreve a chave no arquivo
        p = no_get_valor(no);
        char* nome = paciente_get_nome(p);
        fwrite(&nome, sizeof(nome), 1, fp_lista);
        // Apaga o NO removido
        no_remover(&no);
        paciente_remover_ponteiro(p);
        // Atualiza a variável auxiliar
        lista_pacientes_remover(lista, paciente_get_id((PACIENTE*)no_get_valor(no)));
        no = lista_pacientes_get_no_head(lista);
    }
    // Libera memória
    lista_apagar(&lista);
    fclose(fp_lista); fp_lista = NULL;

    // Salvando os pacientes da TRIAGEM

    FILE *fp_triagem = fopen("triagem.bin", "wb");
    if(!fp_triagem)
        return false;

    no = triagem_get_no_inicio(triagem);
    while(no != NULL) { // Se mantém no while enquanto a TRIAGEM não estiver vazia
        // Escreve a chave no arquivo
        p = no_get_valor(no);
        char* nome = paciente_get_nome(p);
        fwrite(&nome, sizeof(int), 1, fp_triagem);
        // Apaga o NO removido
        no_remover(&no);
        paciente_remover_ponteiro(p);
        // Atualiza a variável auxiliar
        no = TRIAGEM_remover(triagem);
    }
    // Libera memória
    triagem_remover(&triagem);
    fclose(fp_triagem); fp_triagem = NULL;

    return true;
}

bool LOAD(LISTA_PACIENTES **lista, TRIAGEM **fila){
    if(!*lista || !*TRIAGEM) 
        return false;

    PACIENTE* p; // Variável auxiliar
    char* nome;

    // Carregando os pacientes do arquivo na lista

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if(!fp_lista)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&nome, sizeof(nome), 1, fp_lista) == 1) {
        p = paciente_criar(nome, 0);
        lista_pacientes_inserir(*lista, p);
    }
    fclose(fp_lista); // Libera memória

    // Carregando os pacientes do arquivo na TRIAGEM

    FILE *fp_triagem = fopen("triagem.bin", "rb");
    if(!fp_triagem)
        return false;

    // Lê as chaves até o fim do arquivo
    while(fread(&nome, sizeof(nome), 1, fp_triagem) == 1) {
        p = paciente_criar(nome, 0);
        triagem_inserir(*triagem, p);
    }
    fclose(fp_triagem); // Libera memória

    return true;
}