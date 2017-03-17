#include <stdio.h>
#include <math.h>

typedef struct{
	float x;
	float y;
}coordenada;

typedef struct {
	coordenada i;
	coordenada j;
	coordenada k;
	coordenada l; 
   } quadrado;
 
float eConvexo(quadrado quad){}

int main(){
	quadrado q;
	scanf("%f%f",&q.i.x, &q.i.y);
	scanf("%f%f",&q.j.x, &q.j.y);
	scanf("%f%f",&q.k.x, &q.k.y);
	scanf("%f%f",&q.l.x, &q.l.y);

	if(eConvexo()){
		printf("É convexo\n");
	}else{
		printf("Não é convexo\n");
	}

	printf("%f",q.i.x+q.i.y+q.j.x+q.j.y+q.k.x+q.k.y+q.l.x+q.l.y);
	
	return 0;
}
