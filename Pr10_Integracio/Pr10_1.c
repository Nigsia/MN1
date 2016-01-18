#include "../mn.h"
#include "f.h"

#define NUM 2e10
#define PREC 1.e-5

int main( void )
{
	int n;
	double h, t1, t0, dif, a, b;
	FILE *fin, *fout;

	OPEN_IN_FILE( fin );
	OPEN_OUT_FILE( fout );

	fscanf( fin, "%lf %lf", &a, &b );

	n = 1;
	h = b-a;
	t0 = h*(f(b)-f(a))/2.0;
	
	do
	{	
		n = 2*n;
		h = h/2.0;
		t1 = trap( n, h, t0, a, &f );
		dif = fabs( t1-t0 );
		fprintf( fout, "%+.5lf\t %+.5lf\t %+.5lf\n",t0, t1, dif );
		t0 = t1;
	}while( dif > PREC && 2*n < NUM );

	if( dif <= PREC )
		fprintf( fout, "Valor de la integral = %lf\n", t0 );
	else
		fprintf( fout, "No ha convergit.\n" );
	return 0;
}