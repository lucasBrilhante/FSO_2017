#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct _celula{
    int i;
    struct _celula *prox;   
 
}celula;

void bubble(celula *head)
{
	int i;
	int j;
	int aux;
	int k = qtd - 1 ;
	celula *q;
	celula *p;
	while(q !=NULL){
		p=q;
        while(p !=NULL){
        
    
			if(v[j] > v[j+1])
			{
			    aux = v[j];
				v[j] = v[j+1];
				v[j+1]=aux;
			}
		p=p->prox;
		}
	q=q->prox;
	}
	

	printList(v,qtd);
}

int main (int argc, char **argv)
{
	int flag;
	int index;
	int c;
	int temp;
	celula *head,*q;


	while ((c = getopt (argc, argv, "dr")) != -1)
		switch (c)
		{
			case 'd':
				flag = 1;
				break;
			case 'r':
				flag = 0;
			break;

			default:
				break;
		}

	while(temp>0)
	{
		scanf("%d",&temp);
		if(temp >= 0){
			q=head; //guarda o valor de head
        	head=(celula*)malloc(sizeof(celula)); //aloca um endereço
        	head->i=temp; //da valor de i para o endereço de head
        	head->prox=q; //recupera o valor antigo de head
	   	}
	}

	head=q;
	bubble(head);

	while(q !=NULL){
        printf("%d\n",q->info);
        q=q->prox;
    }

	printf ("%d\n",flag);
}