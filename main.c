#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"
#include "fila/fila.h"
#include "triagem/triagem.h"
#include "lista/lista.h"
#include "lista_pacientes/lista_pacientes.h"

int main(void){
    LISTA_PACIENTES* lista_pac = lista_pacientes_criar();
    TRIAGEM* triagem = lista_pacientes_criar();
  
    while(1){
        printf("1. Registrar paciente\n");
        printf("2. Registrar óbito de paciente\n");
        printf("3. Adicionar procedimento ao histórico médico\n");
        printf("4. Desfazer procedimento do histórico médico\n");
        printf("5. Chamar paciente para atendimento\n");
        printf("6. Mostrar fila de espera\n");
        printf("7. Mostrar histórico do paciente\n");
        printf("8. Sair\n");
        int n;
        scanf("%d",&n);
        if(n == 1){
            int id;
            char nome[100];
            scanf(" %d",&id);
            scanf(" %s",nome);
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
        }else if(n == 2){
            int id;
            scanf(" %d",&id);
            bool foi = lista_pacientes_remover(lista_pac,id);
            if(!foi){
                printf("Paciente não encontrado.\n");
            }
        }else if(n == 3){
            int id;
            char item[100];
            scanf(" %d %s",&id, item);
            if(!lista_pacientes_adicionar_procedimento(lista_pac,id,item)){
                printf("Inserção não sucedida.\n");
            }
        }else if(n == 4){
            int id;
            scanf(" %d",&id);
            if(!lista_pacientes_remover_procedimento(lista_pac,id)){
                printf("Remoção não sucedida.\n");
            }
        }else if(n == 5){
            if(triagem_vazia(triagem)){
                printf("Fila de espera vazia.");
            }
            else{
                PACIENTE* paciente = triagem_remover(triagem);
                if(paciente != NULL){
                    printf("Paciente não está na fila de espera.\n");
                }
            }
        }else if(n == 6){
            triagem_imprimir(triagem);
        }else if(n == 7){
            int id;
            scanf("%d",&id);
            PACIENTE* paciente = lista_pacientes_busca(lista_pac, id);
            if(paciente != NULL){
                bool vazia = historico_vazio(paciente_get_historico(paciente));
                if(vazia){
                    printf("Procedimento está vazio\n");
                }else{
                    historico_listar(paciente_get_historico(paciente));
                }
            }else{
                printf("Paciente não encontrado.\n");
            }
        }else{
            break;
        }
    }
    //finalizar o programa


    return 0;
}