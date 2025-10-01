#ifndef IO_H
#define IO_H

#include "../lista_pacientes/lista_pacientes.h"
#include "../triagem/triagem.h"
#include <stdbool.h>

bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *triagem);

bool LOAD(LISTA_PACIENTES *lista, TRIAGEM *triagem);

#endif

	#define IO_H
    #include "../lista/lista.h"
    #include "../triagem/triagem.h"
    #include <stdbool.h>

    bool SAVE(LISTA_PACIENTES *lista, TRIAGEM *fila); // Salva os itens da lista e da fila em arquivos
    bool LOAD(LISTA_PACIENTES **lista, TRIAGEM **fila); // Carrega os itens dos arquivos na lista e na fila
	  
#endif