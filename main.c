#include <stdio.h>
#include <stdlib.h>
#include "pilha/pilha.h"
#include "historico/historico.h"
#include "paciente/paciente.h"
#include "fila/fila.h"
#include "lista/lista.h"

int main(void){
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
            //colocar o paciente na lista e na fila e reportar se deu certo
        }else if(n == 2){
            int id;
            scanf(" %d",&id);
            //retirar o caba da lista e reportar se deu certo
        }else if(n == 3){
            int id,item;
            scanf(" %d %d",&id,&item);
            //adicionar na stack do paciente id o item na stack (reportar se n encontrar)
        }else if(n == 4){
            int id;
            scanf(" %d",&id);
            //desimpilhar a stack do id; (apenas 1) (reportar se nao encontrar o se a pilha estiver vazia)
        }else if(n == 5){
            //retirar o paciente da fila e reportar se a fila estiver vazia
        }else if(n == 6){
            //printar a a lista de espera inteira
        }else if(n == 7){
            int id;
            scanf("%d",&id);
            //printar historico do paciente id
        }else{
            break;
        }
    }
}