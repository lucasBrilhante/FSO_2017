#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	double x = atof(argv[2]);
	char c;
	printf("%lf\n",x);	
	if(argc > 2){
		c = getopt (argc, argv, "as");
		if(c == 's')
			seno(x);
		if(c == 'a')
			arc_seno(x);
	
	}
	else
		printf("Passe o valor do seno desejado");
	return 0;
}