#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h> 

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
    timeval begin,end;
    gettimeofday(begin);
    for(i=0;i<500000;i++){
        printf("a");
    }

    if(childpid == 0){
            gettimeofday(end);
            double time_spent = (double)(end.tv_sec - end.tv_sec);
            printf("pai: %lf\n", time_spent);
        }    
        else{
            gettimeofday(end);
            double time_spent1 = (double)(end.tv_sec - begin.tv_sec);
            printf("filho: %lf\n", time_spent1);
        }

    return 0;
}