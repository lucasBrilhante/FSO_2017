#include "estruturas.h"
#include "func.h"
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

double modulo(double num){
	if(num<0){
		num = num*(-1);
	}
	return num;
}

double calcArea(quadrado quad){
	double area = 0;
	double determinante;
	determinante = modulo(calcDeterminante(quad.i,quad.j,quad.k));
	determinante = determinante + modulo(calcDeterminante(quad.i,quad.l,quad.k));
	area = determinante/2;
	return area;
}

