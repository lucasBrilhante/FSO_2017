#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>


static int *glob_var;

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}

void processoPreg(){
    struct timeval inicio, final;

    while(*glob_var == 0){
    //começa o tempo
    gettimeofday(&inicio, NULL);
    int i = rand()%3;
    //tempo esperado
    waitFor(i);
    //finaliza contagem
    gettimeofday(&final, NULL);

    /* --------Formatando tempo-----------*/

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    int milisegundosF = (int) final.tv_usec;
    int milisegundosI = (int) inicio.tv_usec;
    int milisegundos;
    if(milisegundosI>milisegundosF) milisegundos = milisegundosI - milisegundosF;
    else milisegundos = milisegundosF - milisegundosI;
    int minutos = segundos/60;
    /* ------------------------------------*/
    printf("filho preguiçoso: %d:%d:%d\n",minutos,segundos%60,milisegundos); 
    }
}
/*void processoAtivo(){
    struct timeval inicio, final;
    
    //começa o tempo
    gettimeofday(&inicio, NULL);
    
    //tempo esperado
    /*char buff[10];
    getline(&buff, &sizeof(buff), stdin);

    //finaliza contagem
    gettimeofday(&final, NULL);

    /* --------Formatando tempo-----------

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    int milisegundosF = (int) final.tv_usec;
    int milisegundosI = (int) inicio.tv_usec;
    int milisegundos;
    if(milisegundosI>milisegundosF) milisegundos = milisegundosI - milisegundosF;
    else milisegundos = milisegundosF - milisegundosI;
    int minutos = segundos/60;
    /* ------------------------------------
    printf("%d:%d:%d mensagem: <%s>\n",minutos,segundos%60,milisegundos,buff); 
}*/

int tempoFinal(struct timeval inicio){
    struct timeval final;
    gettimeofday(&final, NULL);

    /* --------Formatando tempo-----------*/

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    
    return segundos;    
}
int main() {
    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *glob_var = 0;

    srand(time(NULL));   // should only be called once
       
    struct timeval inicio, final;
    //começa o tempo
    gettimeofday(&inicio, NULL);

    //criando processos
    pid_t filhoP;
    filhoP = fork();

    //declarando variáveis
    int i, j;
    if(filhoP != 0){
        printf("filho preguiçoso id: %d\n",filhoP); 
        processoPreg(2);
        return 0;
    }
    
    pid_t filhoA;
    filhoA = fork();
    
    if(filhoA != 0){
        printf("filho ativo id: %d\n",filhoA); 
        //processoAtivo();
        return 0;
    }
    printf("filho n pai id: %d\n",filhoA); 
    printf("filho p pai id: %d\n",filhoP); 
    while(tempoFinal(inicio) < 30){}

    *glob_var = 1;
    wait(NULL);
    
    gettimeofday(&final, NULL);

    /* --------Formatando tempo-----------*/

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    int milisegundosF = (int) final.tv_usec;
    int milisegundosI = (int) inicio.tv_usec;
    int milisegundos;
    if(milisegundosI>milisegundosF) milisegundos = milisegundosI - milisegundosF;
    else milisegundos = milisegundosF - milisegundosI;
    int minutos = segundos/60;
    printf("Tempo total: %d:%d:%d\n",minutos,segundos%60,milisegundos ); 

    return 0; 
}