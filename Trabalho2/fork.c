#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h> 

int main(int argv, char *argc[])
{
    clock_t begin = clock();
    int i;
    pid_t childpid;
    childpid = fork();
    if(childpid == -1)
    {
        perror("Failed to Fork");
        return 1;
    }
    for(i=0; i<3; i++)
    {
        if(childpid == 0)
            printf("You are in Child: %ld\n", (long)getpid());
        else
            printf("You are in Parent: %ld\n", (long)getpid());
    }
    return 0;
}