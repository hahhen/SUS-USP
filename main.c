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

    printf("Iniciando teste do sistema SUS-USP...\n\n");

    // 1. Criar estruturas principais
    LISTA_PACIENTES* lista_geral = lista_pacientes_criar();
    TRIAGEM* triagem = triagem_criar();

    if (!lista_geral || !triagem) {
        printf("Erro ao criar estruturas principais.\n");
        return 1;
    }
    printf("Lista de pacientes e fila de triagem criadas.\n");

    // 2. Registrar pacientes dinamicamente
    printf("\nRegistrando pacientes...\n");
    PACIENTE* p1 = paciente_criar("Joao Silva", 101);
    PACIENTE* p2 = paciente_criar("Maria Souza", 102);
    PACIENTE* p3 = paciente_criar("Carlos Pereira", 103);

    lista_pacientes_inserir(lista_geral, p1);
    lista_pacientes_inserir(lista_geral, p2);
    lista_pacientes_inserir(lista_geral, p3);
    printf("Pacientes inseridos na lista geral. Total: %d\n", lista_pacientes_tamanho(lista_geral));
    lista_pacientes_imprimir(lista_geral);


    // 3. Adicionar procedimentos
    printf("\nAdicionando procedimentos médicos...\n");
    paciente_adicionar_procedimento(p1, "Exame de Sangue");
    paciente_adicionar_procedimento(p1, "Raio-X Torax");
    paciente_adicionar_procedimento(p2, "Consulta Cardiologia");
    paciente_adicionar_procedimento(p3, "Tomografia Cranio");
    paciente_adicionar_procedimento(p3, "Eletrocardiograma");

    // 4. Listar procedimentos para verificação
    printf("\nListando procedimentos dos pacientes:\n");
    paciente_listar_procedimentos(p1);
    paciente_listar_procedimentos(p2);
    paciente_listar_procedimentos(p3);

    // 5. Inserir pacientes na fila de triagem
    printf("\nEnviando pacientes para a triagem...\n");
    triagem_inserir(triagem, p1);
    triagem_inserir(triagem, p2);
    triagem_inserir(triagem, p3);
    printf("Pacientes na fila de triagem: %d\n", triagem_tamanho(triagem));

    // 6. Simular atendimento (remover da triagem)
    printf("\nChamando pacientes para atendimento (ordem de prioridade):\n");
    PACIENTE* atendido1 = triagem_remover(triagem);
    if (atendido1) printf("Atendido: %s (ID: %d)\n", paciente_get_nome(atendido1), paciente_get_id(atendido1));
    
    PACIENTE* atendido2 = triagem_remover(triagem);
    if (atendido2) printf("Atendido: %s (ID: %d)\n", paciente_get_nome(atendido2), paciente_get_id(atendido2));

    // Desfazendo um procedimento para teste
    printf("\nDesfazendo ultimo procedimento de %s...\n", paciente_get_nome(p1));
    paciente_remover_procedimento(p1);
    paciente_listar_procedimentos(p1);

    // 7. Remover um paciente da lista geral (simulando óbito ou transferência)
    printf("\nRemovendo paciente com ID 102 da lista geral...\n");
    lista_pacientes_remover(lista_geral, 102);
    printf("Pacientes restantes na lista geral: %d\n", lista_pacientes_tamanho(lista_geral));
    lista_pacientes_imprimir(lista_geral);


    // 8. Liberar toda a memória alocada
    printf("\nFinalizando o sistema e liberando memoria...\n");
    
    // A triagem remove os ponteiros, mas não libera a memória dos pacientes,
    // pois eles ainda existem na lista geral. Vamos esvaziá-la.
    while(!triagem_vazia(triagem)){
        triagem_remover(triagem);
    }
    triagem_apagar(&triagem);
    printf("Memoria da triagem liberada.\n");

    // A função de apagar a lista deve cuidar de remover todos os pacientes restantes.
    lista_pacientes_apagar(&lista_geral);
    printf("Memoria da lista de pacientes e dos pacientes restantes liberada.\n");

    // Os pacientes p1, p2, p3 foram liberados dentro de lista_pacientes_apagar
    // ou em lista_pacientes_remover. Não é necessário (e seria um erro)
    // chamar paciente_remover para eles aqui.

    printf("\nTeste concluido.\n");

    return 0;
}