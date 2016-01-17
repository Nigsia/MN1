#include "../mn.h"
#include "f.h"

double trap( int n, double h, double integral, double a );

int main( void )
{
	int n, num;
	double h, t1, t0, dif, prec, a, b;
	
	num = pow(2,10);
	prec = 1.e-5;	

	n = 1;
	a = 0.0;
	b = 2.0;
	h = b-a;
	t0 = h*(f(b)-f(a))/2.0;
	
	do
	{	
		n = 2*n;
		h = h/2.0;
		t1 = trap( n, h, t0, a );
		dif = fabs( t1-t0 );
		printf("%+.5lf\t %+.5lf\t %+.5lf\n",t0, t1, dif );
		t0 = t1;
	}while( dif > prec && 2*n < num );

	if( dif <= prec )
		printf( "Valor de la integral = %lf\n", t0 );
	else
		printf( "No ha convergit.\n" );
	return 0;
}

double trap( int n, double h, double integral, double a )
{
	int i;
	double res, b = a + n*h;


	res = 0.5*integral;

	for( i = 1; a+i*h < b; i+=2 )
		res += h*f( a + i*h );

	return res;
	
}
