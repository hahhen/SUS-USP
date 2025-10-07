#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"
#include "fila/fila.h"
#include "triagem/triagem.h"
#include "lista/lista.h"
#include "lista_pacientes/lista_pacientes.h"
#include "./io/IO.h"
#include "no/no.h"

int main(void){
    LISTA_PACIENTES* lista_pac = lista_pacientes_criar();
    TRIAGEM* triagem = triagem_criar();
    LOAD(lista_pac,triagem);

    printf("DEBUG:\ntriagem:");
    triagem_imprimir(triagem);
    lista_pacientes_imprimir(lista_pac);

    printf("DEBUG: valor no head lista: %x\n", no_get_valor(lista_get_no_head(lista_pac)));

    while(1){
        printf("\n");
        printf("1. Registrar paciente\n");
        printf("2. Registrar óbito de paciente\n");
        printf("3. Adicionar procedimento ao histórico médico\n");
        printf("4. Desfazer procedimento do histórico médico\n");
        printf("5. Chamar paciente para atendimento\n");
        printf("6. Mostrar fila de espera\n");
        printf("7. Mostrar histórico do paciente\n");
        printf("8. Sair\n");
        printf("\n");
        int n;
        scanf("%d",&n);
        if(n == 1){
            int id;
            char nome[100];
            scanf(" %d",&id);
            scanf(" %s",nome);
            PACIENTE *temp = lista_pacientes_busca(lista_pac,id);
            if(temp != NULL){
                printf("Paciente com esse id já existe\n");
                continue;
            }
            PACIENTE* atual = paciente_criar(nome,id);
            bool foi = lista_pacientes_inserir(lista_pac,atual);
            if(!foi){
                printf("Memória cheia, inserção mal-sucedida\n");
                continue;  
            }
            foi = triagem_inserir(triagem, atual);
            if(!foi){
                lista_pacientes_remover(lista_pac, id);
                printf("Memória cheia, inserção mal-sucedida\n");
                continue;
            }
            printf("Inserção bem sucedida\n");
        }else if(n == 2){
            int id;
            scanf(" %d",&id);
            bool foi = lista_pacientes_remover(lista_pac, id);
            if(!foi){
                printf("Paciente não encontrado.\n");
                continue;
            }
            printf("Paciente removido. (RIP)\n");
        }else if(n == 3){
            int id;
            char item[100];
            scanf(" %d %[^\n]",&id, item);
            // printf("%s\n", item);
            // PACIENTE *temp = lista_pacientes_busca(lista_pac, id);
            // paciente_adicionar_procedimento(temp,item);
            if(!lista_pacientes_busca_id_e_adiciona_procedimento(lista_pac,id,item)){
                printf("Inserção não sucedida.\n");
                continue;
            }
            printf("Inserção bem-sucedida.\n");
        }else if(n == 4){
            int id;
            scanf(" %d",&id);
            if(!lista_pacientes_remover_procedimento(lista_pac,id)){
                printf("Remoção não sucedida.\n");
                continue;
            }
            printf("Remoção bem-sucedida.\n");
        }else if(n == 5){
            if(triagem_vazia(triagem)){
                printf("Fila de espera vazia.\n");
            }
            else{
                PACIENTE* paciente = triagem_remover(triagem);
                if(paciente != NULL){ //acho q aqui não precisa fazer essa checagem
                    printf("Paciente %s chamado para atendimento.\n", paciente_get_nome(paciente));
                }
            }
        }else if(n == 6){
            triagem_imprimir(triagem);
        }else if(n == 7){
            int id;
            scanf("%d",&id);
            PACIENTE* paciente = lista_pacientes_busca(lista_pac, id);
            if(paciente != NULL){
                printf("Histórico do paciente %s (id: %d):\n", paciente_get_nome(paciente), paciente_get_id(paciente));
                bool vazia = historico_vazio(paciente_get_historico(paciente));
                if(vazia){
                    printf("Procedimento está vazio\n");
                }else{
                    printf(historico_listar(paciente_get_historico(paciente)));
                }
            }else{
                printf("Paciente não encontrado.\n");
            }
        }else{
            break;
        }
    }
    //finalizar o programa
    SAVE(lista_pac,triagem);
    // lista_pacientes_apagar(&lista_pac);
    // triagem_apagar(&triagem);
    return 0;
}