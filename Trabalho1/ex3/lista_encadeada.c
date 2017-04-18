#include "lista_encadeada.h"
#include <stdlib.h>
#include <stdio.h>



void imprime_lista(cab *cabecalho) {
    no  *p;
     
    if (cabecalho->tail == NULL) {
        printf("\n\n >> vazio << \n");
    } else {
        p = cabecalho->head;
        while (p != NULL) {
            printf("%d ",p->num);
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

void bubbleSort(cab *cabecalho,char flag){
    no *p = cabecalho->head;
    no *q = cabecalho->head->prox;
    int temp;
    while(p != NULL){
        no *q = p->prox;
        while(q != NULL){
            if(flag == 'r'){
                if((q->num > p->num )){
                    temp = q -> num;
                    q -> num = p-> num;
                    p-> num = temp;
                }
            }else{
                if((q->num < p->num)){
                    temp = q -> num;
                    q -> num = p-> num;
                    p-> num = temp;
                }
            }
            q = q-> prox;
        }
        p = p->prox;
    }
    
    
}