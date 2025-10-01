#include "IO.h"
#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include "../paciente/paciente.h"
#include "../historico/historico.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos de funções auxiliares internas
static void salvar_paciente(FILE *fp, PACIENTE *paciente);
static PACIENTE* carregar_paciente(FILE *fp);

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem) {
    if (!lista || !triagem) return false;

    printf("Salvando dados...\n");

    // Salvar a lista de pacientes
    FILE *fp_lista = fopen("lista_pacientes.dat", "wb");
    if (!fp_lista) return false;

    int tamanho_lista = lista_pacientes_tamanho(lista);
    fwrite(&tamanho_lista, sizeof(int), 1, fp_lista);

    NO *no_atual_lista = lista_pacientes_get_inicio(lista);
    while (no_atual_lista != NULL) {
        salvar_paciente(fp_lista, (PACIENTE*)no_get_valor(no_atual_lista));
        no_atual_lista = no_get_anterior(no_atual_lista);
    }
    fclose(fp_lista);

    // Salvar a fila de triagem
    FILE *fp_triagem = fopen("triagem.dat", "wb");
    if (!fp_triagem) return false;

    int tamanho_triagem = triagem_tamanho(triagem);
    fwrite(&tamanho_triagem, sizeof(int), 1, fp_triagem);

    NO *no_atual_triagem = triagem_get_inicio(triagem);
    printf("Tamanho da triagem para salvar: %d\n", tamanho_triagem);
    while (no_atual_triagem != NULL) {
        printf("Salvando paciente na triagem: %s\n", paciente_get_nome((PACIENTE*)no_get_valor(no_atual_triagem)));
        salvar_paciente(fp_triagem, (PACIENTE*)no_get_valor(no_atual_triagem));
        no_atual_triagem = no_get_anterior(no_atual_triagem);
    }
    fclose(fp_triagem);


    return true;
}

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem) {
    if (!lista || !triagem) return false;

    // Carregar a lista de pacientes
    FILE *fp_lista = fopen("lista_pacientes.dat", "rb");
    if (fp_lista) {
        int tamanho = 0;
        if (fread(&tamanho, sizeof(int), 1, fp_lista) == 1) {
            for (int i = 0; i < tamanho; i++) {
                PACIENTE *p = carregar_paciente(fp_lista);
                if (p) {
                    lista_pacientes_inserir(lista, p);
                } else {
                    fclose(fp_lista);
                    return false; // Arquivo corrompido
                }
            }
        }
        fclose(fp_lista);
    }

    // Carregar a fila de triagem
    FILE *fp_triagem = fopen("triagem.dat", "rb");
    if (fp_triagem) {
        int tamanho = 0;
        if (fread(&tamanho, sizeof(int), 1, fp_triagem) == 1) {
            for (int i = 0; i < tamanho; i++) {
                PACIENTE *p = carregar_paciente(fp_triagem);
                if (p) {
                    triagem_inserir(triagem, p);
                } else {
                    fclose(fp_triagem);
                    return false; // Arquivo corrompido
                }
            }
        }
        fclose(fp_triagem);
    }

    return true;
}

// --- Funções Auxiliares ---

static void salvar_paciente(FILE *fp, PACIENTE *paciente) {
    if (!fp || !paciente) return;

    int id = paciente_get_id(paciente);
    char *nome = paciente_get_nome(paciente);
    HISTORICO *historico = paciente_get_historico(paciente);

    // Escreve ID
    fwrite(&id, sizeof(int), 1, fp);

    // Escreve Nome
    size_t nome_len = strlen(nome);
    fwrite(&nome_len, sizeof(size_t), 1, fp);
    fwrite(nome, sizeof(char), nome_len, fp);

    // Escreve Histórico
    int historico_size = historico_tamanho(historico);
    fwrite(&historico_size, sizeof(int), 1, fp);

    if (historico_size > 0) {
        // Para manter a ordem, salva os procedimentos da base para o topo da pilha
        char **procedimentos = (char **)malloc(sizeof(char *) * historico_size);
        int i = 0;
        NO *no_hist = historico_get_topo(historico);
        while (no_hist != NULL) {
            procedimentos[i++] = (char *)no_get_valor(no_hist);
            no_hist = no_get_anterior(no_hist);
        }

        for (i = historico_size - 1; i >= 0; i--) {
            size_t proc_len = strlen(procedimentos[i]);
            fwrite(&proc_len, sizeof(size_t), 1, fp);
            fwrite(procedimentos[i], sizeof(char), proc_len, fp);
        }
        free(procedimentos);
    }
}

static PACIENTE* carregar_paciente(FILE *fp) {
    if (!fp) return NULL;

    int id;
    size_t nome_len;
    char *nome_buffer = NULL;

    if (fread(&id, sizeof(int), 1, fp) != 1) return NULL;

    if (fread(&nome_len, sizeof(size_t), 1, fp) != 1) return NULL;
    nome_buffer = (char *)malloc(nome_len + 1);
    if (fread(nome_buffer, sizeof(char), nome_len, fp) != nome_len) {
        free(nome_buffer);
        return NULL;
    }
    nome_buffer[nome_len] = '\0';

    PACIENTE *novo_paciente = paciente_criar(nome_buffer, id);
    free(nome_buffer);
    if (!novo_paciente) return NULL;

    int historico_size;
    if (fread(&historico_size, sizeof(int), 1, fp) != 1) {
        paciente_remover(&novo_paciente);
        return NULL;
    }

    for (int i = 0; i < historico_size; i++) {
        size_t proc_len;
        char *proc_buffer = NULL;
        if (fread(&proc_len, sizeof(size_t), 1, fp) != 1) {
            paciente_remover(&novo_paciente);
            return NULL;
        }
        proc_buffer = (char *)malloc(proc_len + 1);
        if (fread(proc_buffer, sizeof(char), proc_len, fp) != proc_len) {
            free(proc_buffer);
            paciente_remover(&novo_paciente);
            return NULL;
        }
        proc_buffer[proc_len] = '\0';
        paciente_adicionar_procedimento(novo_paciente, proc_buffer);
        free(proc_buffer);
    }

    return novo_paciente;

}