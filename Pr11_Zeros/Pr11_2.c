#include "../mn.h"

#define ITER 30
#define PREC 1.e-14
#define INCR 0.01

double f(double x)
{
	return x*x*x - x;
}

int secant(double*, double, int);

//plot "zero.1" w d, "zero.2" w d, "zero.3" w d


int main(void)
{
	double *x;
	double x1, x0;
	FILE *z1, *z0, *z_1;

	z1 = fopen( "zero.1", "w" );	
	z0 = fopen( "zero.2", "w" );	
	z_1 = fopen( "zero.3", "w" );	

	x = dmallocv(2);
 
	for( x0 = -4.0; x0 <= 4.0; x0 += INCR)
	{
		for( x1 = -4.0; x1 <= 4.0; x1 += INCR )
		{
			x[0] = x0;
			x[1] = x1; 
			if( !secant(x, PREC, ITER) )
			{
				if( fabs( x[1]+1.0 ) < PREC )
					fprintf(z1, "%lf %lf\n", x0,x1);
				else if( fabs( x[1] ) < PREC )
					fprintf(z0, "%lf %lf\n", x0,x1);
				else if( fabs( x[1] - 1.0 ) < PREC )
					fprintf(z_1, "%lf %lf\n", x0,x1);			
			}
		}
	}

	secant(x, PREC, ITER);



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
		//printf("x = %lf\tf(x)=%lf\n", x[0], f0 );

	}while( i <= iter && fabs(xincr) >= prec && fabs(f1) >= prec );
	
	if( i > iter )
		return 1;

	return 0;

	
}
