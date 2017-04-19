#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define BUFFER 256


static int *glob_var;
int pipe_child1[2]; /* File descriptors pro pipe do filho preguiçoso*/
int pipe_child2[2]; /* File descriptors pro pipe do filho ativo*/

void SleepFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}
int tempoFinal(struct timeval inicio){
    struct timeval final;
    
    gettimeofday(&final, NULL);

    int segundos = (int) final.tv_sec - inicio.tv_sec;
    
    return segundos;    
}

int get_largest_file_descriptor(int pipe_child1[], int pipe_child2[]){
  int largest;

  largest = pipe_child1[0];

  if (pipe_child1[1] > largest)
    largest = pipe_child1[1];
  if (pipe_child2[0] > largest)
    largest = pipe_child2[0];
  if (pipe_child2[1] > largest)
    largest = pipe_child2[1];

  return largest;
}

void processoPai(struct timeval inicio){
    fd_set read_set;
    struct timeval tv;
    int retval;
    char str_recebida[BUFFER];
    char str_recebida2[BUFFER];
    
    FILE *f = fopen("output.txt", "w");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    while(tempoFinal(inicio) < 30){
        close(pipe_child1[1]);
        close(pipe_child2[1]);

        FD_ZERO(&read_set);
        FD_SET(pipe_child1[0], &read_set);
        FD_SET(pipe_child2[0], &read_set);
        tv.tv_sec = 6;  
        tv.tv_usec = 0;
        retval = select(get_largest_file_descriptor(pipe_child1,pipe_child2)+1, &read_set, NULL, NULL, &tv);

        
        if(retval == -1)
            printf("Select failed.\n");
        else if(retval)
        {
           //printf("Exite pelo menos um pipe ready %d.\n",retval);

            
            if (FD_ISSET(pipe_child1[0], &read_set)){
                /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
                
     
                /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
                read(pipe_child1[0], str_recebida, sizeof(str_recebida));
                //if(strcmp(str_recebida, "")){
                //printf("String enviada pelo filho preg no Pipe : '%s'\n", str_recebida);
                fprintf(f, "%s\n", str_recebida);
                //}
            }
            if (FD_ISSET(pipe_child2[0], &read_set)){
                /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
                read(pipe_child2[0], str_recebida2, sizeof(str_recebida2));
                //if(strcmp(str_recebida2, "")){
                //printf("String enviada pelo filho ativo no Pipe : '%s'\n", str_recebida2);
                fprintf(f, "%s\n", str_recebida2);
                //}
            }           
        }
        else printf("No data written to pipe in 6 last seconds.\n");



        //select(2, &fds, NULL, NULL, NULL);
        /* No filho, vamos ler. Então vamos fechar a entrada de ESCRITA do pipe */
        
        
        
     
        /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
        
        /* print some text */
        //const char *text = "Write this to the file";
        
    }
    fflush(f);
    fclose(f);
}
void processoPreg(struct timeval inicio){
    struct timeval final;
    int count = 0;
    while(*glob_var == 0){
        count++;

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
        sprintf(str,"%d:%d:%d:  Mensagem %d do filho dorminhoco",minutos,segundos%60,milisegundos,count);

        /* Escrevendo a string no pipe */
        write(pipe_child1[1], str, sizeof(str) + 1);
        //printf("filho preguiçoso: %d:%d:%d\n",minutos,segundos%60,milisegundos); 
        int i = rand()%3;
        //tempo esperado
        sleep(i);
    }
}
void processoAtivo(struct timeval inicio){
    struct timeval final;
    int count = 0;
    while(*glob_var == 0){
        count++;
        //começa o tempo
        gettimeofday(&inicio, NULL);
        //Escrever no pipe
        
        //exit(0);
        //char* buff = getline();
        char buff[BUFFER];
        //buff[0] = ' ';
        //printf("Insira a mensagem a qual deseja enviar.\n");
        fflush(stdin);
        scanf("%s", buff);
        getchar();
        //finaliza contagem
        gettimeofday(&final, NULL);

        /* --------Formatando tempo-----------*/

        int segundos = (int) final.tv_sec - inicio.tv_sec;
        int milisegundosF = (int) final.tv_usec;
        int milisegundosI = (int) inicio.tv_usec;
        int milisegundos;
        if(milisegundosI>milisegundosF) milisegundos = milisegundosI - milisegundosF;
        else milisegundos = milisegundosF - milisegundosI;
        int minutos = 0;
        minutos = segundos/60;
        /* ------------------------------------*/
        close(pipe_child2[0]);

        char str[BUFFER];
        sprintf(str,"%d:%d:%d:  Mensagem %d do usuario: <%s>",minutos,segundos%60,milisegundos,count,buff);
        //printf("String enviada para pai no Pipe: '%s'\n", str);

        /* Escrevendo a string no pipe */
        write(pipe_child2[1], str, sizeof(str) + 1);
        //printf("filho preguiçoso: %d:%d:%d\n",minutos,segundos%60,milisegundos); 

        //tempo esperado
    }
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
   
    if(pipe(pipe_child2) < 0) {
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
        processoPreg(inicio);
        return 0;
    }
    //criando processo Ativo
    pid_t filhoA;
    filhoA = fork();
    
    if(filhoA != 0){
        printf("filho ativo id: %d\n",filhoA); 
        processoAtivo(inicio);
        return 0;
    }

    //prova q é o msm pai
    printf("filho a pai id: %d\n",filhoA); 
    printf("filho p pai id: %d\n",filhoP); 
    
    //loop processo pai
    
    //Lê pipe dos filho
    processoPai(inicio);
    //Escreve no arquivo
    

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