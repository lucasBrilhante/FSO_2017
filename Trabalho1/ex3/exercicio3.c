#include <stdio.h>
#include <stdlib.h>
#include "lista_encadeada.h"
 


int main (int argc, char *argv[]) {
    cab *cabecalho;

    char c;
    int i = 0;
     
    cabecalho = (cab *) malloc(sizeof(cab));
    cabecalho->head = NULL;
    cabecalho->tail = NULL;
    
    while(1){
        scanf("%d",&i);
        if(i<0) break;
        insere_final(cabecalho, i);
    }
    c = getopt (argc, argv, "rd");

    bubbleSort(cabecalho,c);

    imprime_lista(cabecalho);

    printf("\n");

    free (cabecalho);
} /* fim-main */

