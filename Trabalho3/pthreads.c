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

void intHandler() {
    keepRunning = 0;
    printf("I aint running\n");
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

void feeder() {
    int i;
    char str[50];
    for(i=0;i<5;i++){
        usleep(100);

        int counter = rand();
        sprintf(str,"[produtor]: numero gerado: %d\n",counter);

        fprintf(f, "%s\n", str);

        enqueue(&counter);


    }
}
void eater() {
    int i;
    char str[50];
    int *value;
    for(i=0;i<5;i++){
        usleep(150);
        value = dequeue();
        sprintf(str,"[consumo a]: numero lido: %d\n",*value);

        fprintf(f, "%s\n", str);


    }
}
void eater2() {
    int i;
    char str[50];
    int *value;
    for(i=0;i<5;i++){
        usleep(150);
        value = dequeue();
        sprintf(str,"[consumo b]: numero lido: %d\n",*value);

        fprintf(f, "%s\n", str);


    }
}
void *threadSeparator(void *vargp)
{
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("First thread processing \n");
        feeder();
    }
    if(pthread_equal(id,tid[1]))
    {
        printf("second thread processing\n");
        eater();
    }
    if(pthread_equal(id,tid[2]))
    {
        printf("Third thread processing\n");
        eater2();
    }

    return NULL;
}
  
int main()
{
    int i = 0, err;
    char fileName[50];
    signal(SIGINT, intHandler);


    printf("Digite o nome do arquivo:  ");
    scanf("%s", fileName);

    f = fopen(fileName, "w");

    init();

    printf("init mutex\n");

    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("mutex init failed\n");
        return 1;
    }


    printf("Iniciando threads\n");

    while(i < 3)
    {
        err = pthread_create(&(tid[i]), NULL, &threadSeparator, NULL);
        if (err != 0)
            printf("can't create thread :[%s]\n", strerror(err));
        i++;
    }

    while(keepRunning);

    printf("Finalizando threads\n");

    //pthread_join(tid[0], NULL);
    //pthread_join(tid[1], NULL);
    //pthread_join(tid[1], NULL);

    exit(0);
}