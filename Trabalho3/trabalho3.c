#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#define N (50)
// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
pthread_t tid[3];

static volatile int keepRunning = 1;
pthread_mutex_t lock;
sem_t countsem, spacesem;
FILE *f;
void *b[N];
int in = 0, out = 0;
int biggest1=0,biggest2=0;
int smallest1=1749241873,smallest2=1749241873; //huge number
int bufferCount=0;



void controller() {
    keepRunning = 0;
    char* str = "[aviso]: Termino solicitado. Aguardando threads...\n";
    fprintf(f, "%s", str);
    printf("\n%s\n", str);

    //Achando o maior de todos
    int biggestOfAll;
    int smallestOfAll;
    if(biggest2 > biggest1){
        biggestOfAll = biggest2;
    }else{
        biggestOfAll = biggest1;
    }

    if(smallest2 > smallest1) {
        smallestOfAll = smallest2;
    }else{
        smallestOfAll = smallest1;
    }
    //Printando maior e menor
    char str2[50];

    sprintf(str2,"[aviso]: Maior numero gerado: %d\n",biggestOfAll);
    fprintf(f, "%s", str2);
    printf("%s\n",str2);

    char str3[50];

    sprintf(str3,"[aviso]: Menor numero gerado: %d\n",smallestOfAll);
    fprintf(f, "%s", str3);
    printf("%s\n",str3);

    char str4[50];

    sprintf(str4,"[aviso]: Maior ocupacao de buffer: %d\n",bufferCount);
    fprintf(f, "%s", str4);
    printf("%s\n",str4);

    char* str5 = "[aviso]: Aplicacao encerrada.\n";
    fprintf(f, "%s\n", str5);
    printf("%s\n",str5);

    fclose(f);
}

void init() {
  sem_init(&countsem, 0, 0);
  sem_init(&spacesem, 0, 50);
}

void enqueue(void *value){
 // wait if there is no space left:
    sem_wait( &spacesem );

    pthread_mutex_lock(&lock);
    b[ (in++) & (N-1) ] = value;
    pthread_mutex_unlock(&lock);

    // increment the count of the number of items
    sem_post(&countsem);
    //verify if buffer bigger
    int j;
    sem_getvalue(&countsem,&j);
    if(j > bufferCount){
        bufferCount = j;
    }

}

void *dequeue(){
    // Wait if there are no items in the buffer
    sem_wait(&countsem);

    pthread_mutex_lock(&lock);
    void *result = b[(out++) & (N-1)];
    pthread_mutex_unlock(&lock);

    // Increment the count of the number of spaces
    sem_post(&spacesem);

    return result;
}
int getRandomNumber(){
    int value = rand();
    int negative = rand()%2;
    if(negative) value*=-1;

    return value;
}
void feeder() {
    int i;
    char str[50];
    while(keepRunning){
        usleep(100000);

        int value = getRandomNumber();

        sprintf(str,"[produtor]: numero gerado: %d\n",value);

        fprintf(f, "%s", str);

        enqueue(&value);


    }
}
void eater() {
    int i;
    char str[50];
    int *value;
    while(keepRunning){

        usleep(150000);
        //read value
        value = dequeue();

        if(*value > biggest1) biggest1 = *value;
        if(*value < smallest1) smallest1 = *value;

        sprintf(str,"[consumo a]: numero lido: %d\n",*value);

        fprintf(f, "%s", str);
    }
}
void eater2() {
    int i;
    char str[50];
    int *value;
    while(keepRunning){

        usleep(150000);
        //read value
        value = dequeue();

        if(*value > biggest2) biggest2 = *value;
        if(*value < smallest2) smallest2 = *value;

        sprintf(str,"[consumo b]: numero lido: %d\n",*value);

        fprintf(f, "%s", str);


    }
}
void *threadSeparator(void *vargp)
{
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        feeder();
    }
    if(pthread_equal(id,tid[1]))
    {
        eater();
    }
    if(pthread_equal(id,tid[2]))
    {
        eater2();
    }

    return NULL;
}
  
int main(int argc, char *argv[])
{
    int i = 0, err;
    char* fileName;
    signal(SIGINT, controller);

    fileName = argv[1];
    

    f = fopen(fileName, "w");
    printf("Arquivo criando: %s\n", fileName);
    init();

    printf("Iniciando componentes\n");

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("mutex init failed\n");
        return 1;
    }


    printf("Iniciando threads\nDigite CTRL+C para terminar\n");

    while(i < 3)
    {
        err = pthread_create(&(tid[i]), NULL, &threadSeparator, NULL);
        if (err != 0)
            printf("can't create thread :[%s]\n", strerror(err));
        i++;
    }

    while(keepRunning);


    //pthread_join(tid[0], NULL);
    //pthread_join(tid[1], NULL);
    //pthread_join(tid[1], NULL);

    exit(0);
}