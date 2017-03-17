#include <stdio.h>
#include <math.h>

#define PI 3.14159265

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

double pitagoras(double x, double y){
	return sqrt((x*x) + (y*y));
} 

int eConvexo(quadrado quad){
	/*double fatorDeConversao = 180.0 / PI;
	double resultado = 0;
	double temp1 = 0;
	double temp2 = 0;
	temp1 = quad.i.x*quad.j.x + quad.i.y*quad.j.y;
	temp2 = pitagoras(quad.i.x,quad.j.x)*pitagoras(quad.i.y, quad.j.y);
	resultado = acos(temp1/temp2) * fatorDeConversao;
	printf("%lf\n",resultado);*/
	return 1;
}

int main(){
	quadrado q;
	scanf("%f%f",&q.i.x, &q.i.y);
	scanf("%f%f",&q.j.x, &q.j.y);
	scanf("%f%f",&q.k.x, &q.k.y);
	scanf("%f%f",&q.l.x, &q.l.y);

	if(eConvexo(q) == 1){
		printf("É convexo\n");
	}else{
		printf("Não é convexo\n");
	}
	
	return 0;
}
