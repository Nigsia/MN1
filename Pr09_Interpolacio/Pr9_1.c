#include "../mn.h"

#define M 50

double fun(double x)
{
	return cos(x);
}

double dfun(double x)
{
	return -sin(x);
}

int main( void )
{
	int n, i, indic;
	double min, max, *x, *f, h, p[2];
	FILE *fin, *fout;

	OPEN_IN_FILE( fin );
	OPEN_OUT_FILE( fout );

	fscanf(fin, "%d", &n);
	fscanf(fin, "%d", &indic);
	fscanf(fin, "%lf %lf", &min, &max);

	x = dmallocv( n+1 );
	f = dmallocv( n+1 );

	nodes( indic, n, min, max, x );

	for( i = 0; i <= n; i++ )
		f[i] = fun( x[i] );

	difdiv( n+1, x, f );
	
	fprintf( fout, "#z\tf(z)\tf'(z)\tp(z)\tp'(z)\n" );
	
	h = (max-min)/M;
	
	for( i = 0; i <= M; i++ )
	{
		hornerd( min+i*h, n, x, f, p );
		fprintf( fout, "%+.4lf\t%+.4lf\t%+.4lf\t%+.4lf\t%+.4lf\n", min+i*h, fun( min+i*h ), dfun( min+i*h ), p[0], p[1] );
	}

	return 0;
}