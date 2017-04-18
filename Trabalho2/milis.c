#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    //criando processos
    pid_t childpid;
    childpid = fork();

    //declarando variáveis
    int i, j;
    struct timeval inicio, final;
    int tmili;
    //começa o tempo
    gettimeofday(&inicio, NULL);
    
    //tempo medido
    for (j = 0; j < 10; j ++) 
        for (i = 0; i < 138763434; i ++); 
    //finaliza contagem
    gettimeofday(&final, NULL);

    //formatando tempo
    int segundos = (int) final.tv_sec - inicio.tv_sec;
    int milisegundos = (int) final.tv_usec - inicio.tv_usec;
    int minutos = segundos/60;

    //printando
    if(childpid == 0){
        printf("tempo decorrido pai: %d:%d:%d\n",minutos,segundos%60,milisegundos ); 
    }else{
        printf("tempo decorrido filho: %d:%d:%d\n",minutos,segundos%60,milisegundos ); 

    }
    return 0; 
}