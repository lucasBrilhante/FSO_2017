#ifndef _func_
#define _func_

typedef struct _no {
    int num;
    struct _no  *prox;
} no;
typedef struct _cab {
    struct _no  *head;
    struct _no  *tail;
} cab;


void imprime_lista(cab *cabecalho);
void insere_final(cab *cabecalho, int i);
void bubbleSort(cab *cabecalho,char flag);

#endif