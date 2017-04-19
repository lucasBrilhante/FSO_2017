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

#define BUFFER 256


static int *glob_var;
int pipe_child1[2]; /* File descriptors pro pipe do filho preguiçoso*/
int pipe_child2[2]; /* File descriptors pro pipe do filho ativo*/

void SleepFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
void processoPai(){
     char str_recebida[BUFFER];
 
    /* No filho, vamos ler. Então vamos fechar a entrada de ESCRITA do pipe */
    close(pipe_child1[1]);
 
    /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
    read(pipe_child1[0], str_recebida, sizeof(str_recebida));
 
    printf("String enviada pelo filho no Pipe : '%s'\n", str_recebida);
}
void processoPreg(){
    struct timeval inicio, final;

    while(*glob_var == 0){
    //começa o tempo
    gettimeofday(&inicio, NULL);
    //Escrever no pipe
    
    //exit(0);

    printf("oi\n"); 
    int i = rand()%3;
    //tempo esperado
    SleepFor(i);
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
    close(pipe_child1[0]);

    char str[BUFFER];
    sprintf(str,"filho preguiçoso: %d:",minutos);//,minutos,segundos%60,milisegundos);
    sprintf(str,"%d:",segundos%60);
    sprintf(str,"%d",milisegundos);
    printf("String enviada para pai no Pipe: '%s'", str);

    /* Escrevendo a string no pipe */
    write(pipe_child1[1], str, sizeof(str) + 1);
    //printf("filho preguiçoso: %d:%d:%d\n",minutos,segundos%60,milisegundos); 
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

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    
    return segundos;    
}
int main() {

    /*--------------setup---------------------*/
    //Inicializando flag
    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *glob_var = 0;
    //Inicializando pipe
    if(pipe(pipe_child1) < 0) {
        perror("Error creating pipe for child1") ;
        return -1 ;
    }
   
    if(pipe(pipe_child1) < 0) {
        perror("Error creating pipe for child2") ;
        return -1 ;
    }
    //inializando rand
    srand(time(NULL));   // should only be called once
    int i, j;
       
    struct timeval inicio, final;
    //começa o tempo
    gettimeofday(&inicio, NULL);
    /*------------------setup-----------------*/


    //criando processo preguiçoso
    pid_t filhoP;
    filhoP = fork();

    
    if(filhoP != 0){
        printf("filho preguiçoso id: %d\n",filhoP); 
        processoPreg();
        return 0;
    }
    //criando processo Ativo
    pid_t filhoA;
    filhoA = fork();
    
    if(filhoA != 0){
        printf("filho ativo id: %d\n",filhoA); 
        //processoAtivo();
        return 0;
    }

    //prova q é o msm pai
    printf("filho a pai id: %d\n",filhoA); 
    printf("filho p pai id: %d\n",filhoP); 
    
    //loop processo pai
    while(tempoFinal(inicio) < 30){
        //Lê pipe dos filho
        processoPai();
        //Escreve no arquivo
    }

    //flag para os filhos terminarem
    *glob_var = 1;
    //Espera os filhos
    wait(NULL);
    //finaliza tempo
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