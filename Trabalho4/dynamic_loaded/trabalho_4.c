#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]){
	double x = atof(argv[2]);
	char c;

	void *lib_handle;
	void (*fn)(double);
	char *error;

	lib_handle = dlopen("./libseno.so", RTLD_LAZY);
	if (!lib_handle) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}

	if(argc > 2){
		c = getopt (argc, argv, "as");
		if(c == 's'){
			fn = dlsym(lib_handle, "seno");
			if ((error = dlerror()) != NULL)  
			{
				fprintf(stderr, "%s\n", error);
				exit(1);
			}

			(*fn)(x);
		}
		if(c == 'a'){
			fn = dlsym(lib_handle, "arc_seno");
			if ((error = dlerror()) != NULL)  
			{
				fprintf(stderr, "%s\n", error);
				exit(1);
			}

			(*fn)(x);
		}
	}
	else
		printf("Passe o valor do seno desejado");
	return 0;
}