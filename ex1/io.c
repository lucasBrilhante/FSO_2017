#include "estruturas.h"
#include <stdio.h>
#include "io.h"

quadrado getInput(){
	quadrado q;
	scanf("%lf%lf",&q.i.x, &q.i.y);
	scanf("%lf%lf",&q.j.x, &q.j.y);
	scanf("%lf%lf",&q.k.x, &q.k.y);
	scanf("%lf%lf",&q.l.x, &q.l.y);

	return q;
}