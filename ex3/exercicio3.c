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
