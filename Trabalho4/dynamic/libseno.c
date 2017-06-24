#include <stdio.h>

double fatorial(int m)
{
    if (m==0 || m==1) return (1);
    else return (m*fatorial(m-1));
}
double elevado(double x,int n)
{
    double val=1;
    int i;
    for (i=1;i<=n;i++)
    {
        val*=x;
    }
    return val;
}

void seno(double x)
{
    int n;
    double val=0;
    for (n=0;n<5;n++)
    {
        val += (elevado(-1,n) * elevado(x,2*n+1) / fatorial(2*n+1));        
    }

    printf("seno(%.2lf) = %lf\n",x,val);
}

void arc_seno(double x)
{
    double last=x;
    double sum=last;
    int i;
    int n = 3000;
    for(i=1;i<=n;i++)
    {
        last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
        sum+=last;
    }
    printf("arcsin(%lf) = %lf\n",x,sum);
}

