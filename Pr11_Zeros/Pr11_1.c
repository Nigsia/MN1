#include "../mn.h"

double f(double x)
{
	return x*x*x - x;
}

int secant(double*, double, int);

int main(void)
{
	double *x;

	x = dmallocv(2);
	x[0] = 3;
	x[1] = 2;

	secant(x, 1.e-15, 20);

	printf("Secant %lf\n", x[0] );

	return 0;
}

/*
 *	x_{n+1} = x_n - f(x_n) ( x_n - x_{n-1} )/( f(x_n) - f(x_{n-1}) )
 *  x és un vector de dues components
 */
int secant(double *x, double prec, int iter)
{
	double xincr, f0, f1;
	int i;

	f0 = f(x[0]);
	f1 = f(x[1]);
	
	i = 0;

	do
	{
		
		i++;
		if( fabs( f1-f0 ) < prec ) 
			return 1;
		xincr = f1*( x[1] - x[0] )/( f1-f0 );
		x[0] = x[1];
		f0 = f1;
		x[1] = x[1] - xincr;
		f1 = f(x[1]);
		printf("x = %lf\tf(x)=%lf\n", x[0], f0 );

	}while( i <= iter && fabs(xincr) >= prec && fabs(f1) >= prec );
	
	if( i > iter )
		return 1;

	return 0;

	
}
