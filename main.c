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
            int id,item;
            scanf(" %d %d",&id,&item);
            PACIENTE* paciente = lista_pacientes_busca(lista_pac, id);
            //TENTAR SIMPLIFICAR ISSO AQUI DEPOIS (pra n ficar dando find e depois adicionar)
            if(paciente != NULL){
                bool foi = paciente_adicionar_procedimento(paciente,item);
                if(!foi){
                    printf("Inserção não sucedida\n");
                }
            }else{
                printf("Paciente não encontrado.\n");
            }
        }else if(n == 4){
            int id;
            scanf(" %d",&id);
            PACIENTE* paciente = lista_pacientes_busca(lista_pac, id);
            if(paciente != NULL){
                bool foi = paciente_remover_procedimento(paciente);
                if(!foi){
                    printf("Procedimento está vazio\n");
                }
            }else{
                printf("Paciente não encontrado.\n");
            }
        }else if(n == 5){
            bool foi = triagem_remover(triagem);
            if(!foi){
                printf("Procedimento já estava vazio\n");
            }
        }else if(n == 6){
            //printar a a lista de espera inteira (NAO EXISTE ESSA FUNCAO)
            //triagem_imprimir()
        }else if(n == 7){
            int id;
            scanf("%d",&id);
            //printar historico do paciente id ESSE AQUI SÓ N SEI MESMO
            PACIENTE* paciente = lista_pacientes_busca(lista_pac, id);
            if(paciente != NULL){
                bool foi = paciente_imp(paciente);
                if(!foi){
                    printf("Procedimento está vazio\n");
                }
            }else{
                printf("Paciente não encontrado.\n");
            }
        }else{
            break;
        }
    }
    //finalizar o programa

}