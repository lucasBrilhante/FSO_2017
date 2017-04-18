#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h> 

int main(int argv, char *argc[])
{
    
    int i;
    pid_t childpid;
    childpid = fork();
    if(childpid == -1)
    {
        perror("Failed to Fork");
        return 1;
    }
    clock_t begin = clock();
            
    for(i=0;i<500000;i++){
        printf("a");
    }

    if(childpid == 0){
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("pai: %lf\n", time_spent);
        }    
        else{
            clock_t end1 = clock();
            double time_spent1 = (double)(end1 - begin) / CLOCKS_PER_SEC;
            printf("filho: %lf\n", time_spent1);
        }

    return 0;
}