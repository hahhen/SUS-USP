#include "IO.h"
#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include "../paciente/paciente.h"
#include "../historico/historico.h"
#include "../no/no.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Protótipos ---
static void salvar_paciente_completo(FILE *fp, PACIENTE *paciente);
static PACIENTE *carregar_paciente_completo(FILE *fp);

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem)
{
    if (!lista || !triagem)
        return false;

    remove("lista_pacientes.dat");

    printf("Salvando dados...\n");

    // 1. Salvar a lista de pacientes (objetos completos)
    FILE *fp_lista = fopen("lista_pacientes.dat", "wb");
    if (!fp_lista)
        return false;

    int tamanho_lista = lista_pacientes_tamanho(lista);
    fwrite(&tamanho_lista, sizeof(int), 1, fp_lista);

    NO *no_atual_lista = lista_pacientes_get_inicio(lista);
    if (no_atual_lista != NULL) {
        no_atual_lista = no_get_anterior(no_atual_lista); // Pula o nó sentinela
    }
    while (no_atual_lista != NULL)
    {
        printf("DEBUG: SAVE: paciente carregado: %x\n", (PACIENTE *)no_get_valor(no_atual_lista));

        salvar_paciente_completo(fp_lista, (PACIENTE *)no_get_valor(no_atual_lista));
        no_atual_lista = no_get_anterior(no_atual_lista);
    }
    fclose(fp_lista);

    // // 2. Salvar a fila de triagem (apenas IDs)
    // FILE *fp_triagem = fopen("triagem.dat", "wb");
    // if (!fp_triagem)
    //     return false;

    // int tamanho_triagem = triagem_tamanho(triagem);
    // fwrite(&tamanho_triagem, sizeof(int), 1, fp_triagem);

    // NO *no_atual_triagem = triagem_get_inicio(triagem);
    // if (no_atual_triagem != NULL) {
    //     no_atual_triagem = no_get_anterior(no_atual_triagem); // Pula o nó sentinela
    // }
    // while (no_atual_triagem != NULL)
    // {
    //     PACIENTE *p = (PACIENTE *)no_get_valor(no_atual_triagem);
    //     int id = paciente_get_id(p);
    //     fwrite(&id, sizeof(int), 1, fp_triagem); // Salva apenas o ID
    //     no_atual_triagem = no_get_anterior(no_atual_triagem);
    // }
    // fclose(fp_triagem);

    return true;
}

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem)
{
    if (!lista || !triagem)
        return false;

    // 1. Carregar todos os pacientes para a lista principal
    FILE *fp_lista = fopen("lista_pacientes.dat", "rb");
    if (fp_lista)
    {
        int tamanho = 0;
        if (fread(&tamanho, sizeof(int), 1, fp_lista) == 1)
        {
            for (int i = 0; i < tamanho; i++)
            {
                PACIENTE *p = carregar_paciente_completo(fp_lista);
                printf("DEBUG: LOAD: paciente carregado: %x\n", p);
                if (p)
                {
                    // Insere apenas na lista principal
                    lista_pacientes_inserir(lista, p);
                    if(get_esta_em_triagem(p)) {
                        triagem_inserir(triagem, p);
                    }
                }
                else
                {
                    fclose(fp_lista);
                    return false; // Arquivo corrompido
                }
            }
        }
        fclose(fp_lista);
    }

    // // 2. Carregar a fila de triagem usando os IDs e a lista já populada
    // FILE *fp_triagem = fopen("triagem.dat", "rb");
    // if (fp_triagem)
    // {
    //     int tamanho = 0;
    //     if (fread(&tamanho, sizeof(int), 1, fp_triagem) == 1)
    //     {
    //         for (int i = 0; i < tamanho; i++)
    //         {
    //             int id;
    //             if (fread(&id, sizeof(int), 1, fp_triagem) != 1)
    //             {
    //                 fclose(fp_triagem);
    //                 return false; // Erro de leitura
    //             }

    //             // Busca o paciente já carregado na lista principal pelo ID
    //             PACIENTE *p = lista_pacientes_busca(lista, &id);
    //             if (p)
    //             {
    //                 // Insere o ponteiro existente na fila de triagem
    //                 triagem_inserir(triagem, p);
    //             }
    //             // Se p for nulo, o paciente pode ter sido removido, então é seguro ignorar.
    //         }
    //     }
    //     fclose(fp_triagem);
    // }

    return true;
}

// --- Funções Auxiliares ---

static void salvar_paciente_completo(FILE *fp, PACIENTE *paciente)
{
    if (!fp || !paciente)
        return;

    int id = paciente_get_id(paciente);
    char *nome = paciente_get_nome(paciente);
    bool esta_em_triagem = get_esta_em_triagem(paciente); // Pega a flag
    HISTORICO *historico = paciente_get_historico(paciente);

    // Escreve ID
    fwrite(&id, sizeof(int), 1, fp);

    // Escreve Nome
    size_t nome_len = strlen(nome);
    fwrite(&nome_len, sizeof(size_t), 1, fp);
    fwrite(nome, sizeof(char), nome_len, fp);

    printf("DEBUG: SAVE: salvando paciente %s, id %d, esta em triagem? %d\n", nome, id, esta_em_triagem);

    // Escreve a flag de triagem
    fwrite(&esta_em_triagem, sizeof(bool), 1, fp);

    // Escreve Histórico
    int historico_size = historico_tamanho(historico);
    fwrite(&historico_size, sizeof(int), 1, fp);

    if (historico_size > 0)
    {
        // Para manter a ordem, salva os procedimentos da base para o topo da pilha
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

    // Lê a flag de triagem do arquivo
    if (fread(&esta_em_triagem, sizeof(bool), 1, fp) != 1)
    {
        free(nome_buffer);
        return NULL;
    }

    // Usa a flag lida para criar o paciente
    PACIENTE *novo_paciente = paciente_criar(nome_buffer, id, esta_em_triagem);
    printf("DEBUG LOAD: o paciente %s esta em triagem? %d\n", paciente_get_nome(novo_paciente), get_esta_em_triagem(novo_paciente));
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