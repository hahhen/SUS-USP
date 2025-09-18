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

    // LISTA_PACIENTES* lista = lista_pacientes_criar();
    // TRIAGEM* triagem = triagem_criar();

    // PACIENTE* p1 = paciente_criar("Joao", 1);
    // PACIENTE* p2 = paciente_criar("Maria", 2);
    // PACIENTE* p3 = paciente_criar("Ana", 3);

    // lista_pacientes_inserir(lista,p1);
    // lista_pacientes_inserir(lista,p2);
    // lista_pacientes_inserir(lista,p3);

    // paciente_adicionar_procedimento(p1,"Exame de sangue");
    // paciente_adicionar_procedimento(p1,"Raio-X");

    // paciente_remover_procedimento(p1);

    // paciente_listar_procedimentos(p1);

    // triagem_inserir(triagem,p1);
    // triagem_inserir(triagem,p2);

    // lista_pacientes_remover(lista,3);

    // lista_pacientes_imprimir(lista);


    // while(1){
    //     printf("1. Registrar paciente\n");
    //     printf("2. Registrar óbito de paciente\n");
    //     printf("3. Adicionar procedimento ao histórico médico\n");
    //     printf("4. Desfazer procedimento do histórico médico\n");
    //     printf("5. Chamar paciente para atendimento\n");
    //     printf("6. Mostrar fila de espera\n");
    //     printf("7. Mostrar histórico do paciente\n");
    //     printf("8. Sair\n");
    //     int n;
    //     scanf("%d",&n);
    //     if(n == 1){
    //         int id;
    //         char nome[100];
    //         scanf(" %d",&id);
    //         scanf(" %s",nome);
    //         //colocar o paciente na lista e na fila e reportar se deu certo
    //     }else if(n == 2){
    //         int id;
    //         scanf(" %d",&id);
    //         //retirar o caba da lista e reportar se deu certo
    //     }else if(n == 3){
    //         int id,item;
    //         scanf(" %d %d",&id,&item);
    //         //adicionar na stack do paciente id o item na stack (reportar se n encontrar)
    //     }else if(n == 4){
    //         int id;
    //         scanf(" %d",&id);
    //         //desimpilhar a stack do id; (apenas 1) (reportar se nao encontrar o se a pilha estiver vazia)
    //     }else if(n == 5){
    //         //retirar o paciente da fila e reportar se a fila estiver vazia
    //     }else if(n == 6){
    //         //printar a a lista de espera inteira
    //     }else if(n == 7){
    //         int id;
    //         scanf("%d",&id);
    //         //printar historico do paciente id
    //     }else{
    //         break;
    //     }
    // }


}