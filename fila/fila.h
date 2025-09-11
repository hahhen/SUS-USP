#ifndef _FILA_H
#define _FILA_H

  #include "../no/no.h"
  #include <stdbool.h>
  #include <string.h>

  typedef struct fila FILA;

  FILA* fila_criar(void);
  void fila_apagar(FILA** fila);
  bool fila_vazia(FILA* fila);
  bool fila_cheia(FILA* fila);
  int fila_tamanho(FILA* fila);
  void* fila_remover(FILA* fila);
  bool fila_inserir(FILA* fila, void* valor);

#endif 
