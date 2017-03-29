#include <stdio.h>
#include <math.h>

#include "estruturas.h"
#include "func.h"

#define PI 3.14159265

int main(){
	quadrado q;
	scanf("%lf%lf",&q.i.x, &q.i.y);
	scanf("%lf%lf",&q.j.x, &q.j.y);
	scanf("%lf%lf",&q.k.x, &q.k.y);
	scanf("%lf%lf",&q.l.x, &q.l.y);

	if(eConvexo(q) == 0){
		printf("É convexo\n");
		printf("Area:%lf.\n",calcArea(q));
	}else{
		printf("Não é convexo\n");
	}
	
	return 0;
}
