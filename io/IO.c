#include "IO.h"
#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include "../paciente/paciente.h"
#include "../historico/historico.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void salvar_paciente_completo(FILE *fp, PACIENTE *paciente);
static PACIENTE *carregar_paciente_completo(FILE *fp);

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem)
{
    if (!lista || !triagem)
        return false;

    remove("lista_pacientes.dat");

    printf("Salvando dados...\n");

    FILE *fp_lista = fopen("lista_pacientes.dat", "wb");
    if (!fp_lista)
        return false;

    int tamanho_lista = lista_pacientes_tamanho(lista);
    fwrite(&tamanho_lista, sizeof(int), 1, fp_lista);

    NO *no_atual_lista = lista_pacientes_get_inicio(lista);
    if (no_atual_lista != NULL) {
        no_atual_lista = no_get_anterior(no_atual_lista);
    }
    while (no_atual_lista != NULL)
    {

        salvar_paciente_completo(fp_lista, (PACIENTE *)no_get_valor(no_atual_lista));
        no_atual_lista = no_get_anterior(no_atual_lista);
    }
    fclose(fp_lista);
    return true;
}

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem)
{
    if (!lista || !triagem)
        return false;

    FILE *fp_lista = fopen("lista_pacientes.dat", "rb");
    if (fp_lista)
    {
        int tamanho = 0;
        if (fread(&tamanho, sizeof(int), 1, fp_lista) == 1)
        {
            for (int i = 0; i < tamanho; i++)
            {
                PACIENTE *p = carregar_paciente_completo(fp_lista);
                // printf("DEBUG: LOAD: paciente carregado: %x\n", p);
                if (p)
                {
                    lista_pacientes_inserir(lista, p);
                    if(get_esta_em_triagem(p)) {
                        triagem_inserir(triagem, p);
                    }
                }
                else
                {
                    fclose(fp_lista);
                    return false;
                }
            }
        }
        fclose(fp_lista);
    }
    return true;
}

static void salvar_paciente_completo(FILE *fp, PACIENTE *paciente)
{
    if (!fp || !paciente)
        return;

    int id = paciente_get_id(paciente);
    char *nome = paciente_get_nome(paciente);
    bool esta_em_triagem = get_esta_em_triagem(paciente);
    HISTORICO *historico = paciente_get_historico(paciente);

    fwrite(&id, sizeof(int), 1, fp);

    size_t nome_len = strlen(nome);
    fwrite(&nome_len, sizeof(size_t), 1, fp);
    fwrite(nome, sizeof(char), nome_len, fp);

    // printf("DEBUG: SAVE: salvando paciente %s, id %d, esta em triagem? %d\n", nome, id, esta_em_triagem);

    fwrite(&esta_em_triagem, sizeof(bool), 1, fp);

    int historico_size = historico_tamanho(historico);
    fwrite(&historico_size, sizeof(int), 1, fp);

    if (historico_size > 0)
    {
        char **procedimentos = (char **)malloc(sizeof(char *) * historico_size);
        int i = 0;
        NO *no_hist = historico_get_topo(historico);
        while (no_hist != NULL)
        {
            procedimentos[i++] = (char *)no_get_valor(no_hist);
            no_hist = no_get_anterior(no_hist);
        }

        for (i = historico_size - 1; i >= 0; i--)
        {
            size_t proc_len = strlen(procedimentos[i]);
            fwrite(&proc_len, sizeof(size_t), 1, fp);
            fwrite(procedimentos[i], sizeof(char), proc_len, fp);
        }
        free(procedimentos);
    }
}

static PACIENTE *carregar_paciente_completo(FILE *fp)
{
    if (!fp)
        return NULL;

    int id;
    size_t nome_len;
    char *nome_buffer = NULL;
    bool esta_em_triagem;

    if (fread(&id, sizeof(int), 1, fp) != 1)
        return NULL;

    if (fread(&nome_len, sizeof(size_t), 1, fp) != 1)
        return NULL;
    nome_buffer = (char *)malloc(nome_len + 1);
    if (fread(nome_buffer, sizeof(char), nome_len, fp) != nome_len)
    {
        free(nome_buffer);
        return NULL;
    }
    nome_buffer[nome_len] = '\0';

    if (fread(&esta_em_triagem, sizeof(bool), 1, fp) != 1)
    {
        free(nome_buffer);
        return NULL;
    }

    PACIENTE *novo_paciente = paciente_criar(nome_buffer, id, esta_em_triagem);
    // printf("DEBUG LOAD: o paciente %s esta em triagem? %d\n", paciente_get_nome(novo_paciente), get_esta_em_triagem(novo_paciente));
    free(nome_buffer);
    if (!novo_paciente)
        return NULL;

    int historico_size;
    if (fread(&historico_size, sizeof(int), 1, fp) != 1)
    {
        paciente_remover(&novo_paciente);
        return NULL;
    }

    for (int i = 0; i < historico_size; i++)
    {
        size_t proc_len;
        char *proc_buffer = NULL;
        if (fread(&proc_len, sizeof(size_t), 1, fp) != 1)
        {
            paciente_remover(&novo_paciente);
            return NULL;
        }
        proc_buffer = (char *)malloc(proc_len + 1);
        if (fread(proc_buffer, sizeof(char), proc_len, fp) != proc_len)
        {
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