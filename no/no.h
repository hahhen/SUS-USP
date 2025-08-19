#ifndef NO_H
#define NO_H

typedef struct No NO;

NO* no_criar(void* valor, NO* anterior);

NO* no_get_anterior(NO* no);

void no_remover(NO **no);

#endif