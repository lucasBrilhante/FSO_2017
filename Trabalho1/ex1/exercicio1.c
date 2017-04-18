#include <math.h>
#include <stdio.h>
#include "estruturas.h"
#include "func.h"
#include "io.h"

#define PI 3.14159265

int main(){
	quadrado q = getInput();
	double result;

	if(eConvexo(q) == 0){
		result = calcArea(q);
		printf("É convexo\n");
		printf("Area:%.2lf\n",result);
	}else{
		printf("Não é convexo\n");
	}
	
	return 0;
}
