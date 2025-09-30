#ifndef TRIAGEM_H
#define TRIAGEM_H

    #include "../fila/fila.h"
    #include <stdlib.h>
    #include "../paciente/paciente.h"
    #define TAM_MAX 10000

    typedef struct triagem TRIAGEM;

    TRIAGEM *triagem_criar();
    bool triagem_inserir(TRIAGEM *triagem, PACIENTE *paciente);
    PACIENTE *triagem_remover(TRIAGEM *triagem);
    bool triagem_vazia(TRIAGEM *triagem);
    bool triagem_cheia(TRIAGEM *triagem);
    int triagem_tamanho(TRIAGEM *triagem);
    void triagem_imprimir(TRIAGEM *triagem);
    void triagem_apagar(TRIAGEM **triagem);
    NO* triagem_get_no_inicio(TRIAGEM *triagem);

#endif
