#include <stdio.h>
#include <math.h>

#define PI 3.14159265



typedef struct{
	double x;
	double y;
}coordenada;

typedef struct {
	coordenada i;
	coordenada j;
	coordenada k;
	coordenada l; 
   } quadrado;



double calcDeterminante(coordenada c1, coordenada c2, coordenada c3){
	double resultado;

	resultado = (c1.x*c2.y) + (c1.y*c3.x) + (c2.x*c3.y) -
	 ((c1.y*c2.x) + (c1.x*c3.y) + (c2.y*c3.x));
	return resultado;
}


int eConvexo(quadrado quad){
	double resultado = 0;
	double determinante;

	determinante = calcDeterminante(quad.i,quad.j,quad.k);
	if(determinante > 0)
		resultado = 1;
	determinante = calcDeterminante(quad.j,quad.k,quad.l);
	if(determinante > 0)
		resultado = 1;
	determinante = calcDeterminante(quad.k,quad.l,quad.i);
	if(determinante > 0)
		resultado = 1;
	determinante = calcDeterminante(quad.l,quad.i,quad.j);
	if(determinante > 0)
		resultado = 1;

	return resultado;
}

double calcArea(quadrado quad){
	double area = 0;
	double determinante;
	determinante = abs(calcDeterminante(quad.i,quad.j,quad.k));
	determinante = determinante + abs(calcDeterminante(quad.i,quad.l,quad.k));
	area = determinante/2;
	return area;
}

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
