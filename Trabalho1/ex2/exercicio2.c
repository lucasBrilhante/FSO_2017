#include <stdio.h>

 int main(int argc, char *argv[])
{
   	printf("# de parametros #%d\n",argc);

    int i = 1;
    for (i = 1; i < argc; i++) {
        printf("Parametro #%d : %s\n", i, argv[i]);
    }
    return 0;
}