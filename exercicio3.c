#include <stdio.h>
#include <stdlib.h>

 
typedef struct _no {
    int num;
    struct _no  *prox;
} no;
typedef struct _cab {
    struct _no  *head;
    struct _no  *tail;
} cab;

void imprime_lista(cab *cabecalho) {
    no  *p;
     
    if (cabecalho->tail == NULL) {
        printf("\n\n >> cab vazia << \n");
    } else {
        printf("Primeiro no: %d \n",cabecalho->head->num);
        printf("Ultimo   no: %d \n",cabecalho->tail->num);
        p = cabecalho->head;
        while (p != NULL) {
            printf("%d \n",p->num);
            p = p->prox;
        } /* fim-while */
    }
    printf("\n");
}

void insere_final(cab *cabecalho, int i) {
    no  *novo;
    int n;
     
 
    novo = (no *) malloc(sizeof(no));
    novo->num=i;
    novo->prox = NULL;

    if (cabecalho->tail == NULL) {
        cabecalho->tail = novo;
        cabecalho->head = novo;
    } else {
        cabecalho->tail->prox = novo;
        cabecalho->tail = novo; 
    }

} 

int main (void) {
    cab *cabecalho;

    int n;
    int i;
     
    cabecalho = (cab *) malloc(sizeof(cab));
    cabecalho->head = NULL;
    cabecalho->tail = NULL;
    
    for(i = 0; i<10 ; i++){
        insere_final(cabecalho, i);
    }
    imprime_lista(cabecalho);
    printf("\n");
    free (cabecalho);
} /* fim-main */
