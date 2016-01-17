#include "../mn.h"

#define N 20
#define M 100
#define SPACE printf("\n");

void difdiv( int, double*, double* );
double horner( double, int, double*, double* );

int main( void )
{
	int n, i = 0;
	double *x, *f;
	double z, h;
	FILE *fin, *fout;

	fin = fopen( "in.dad", "r" );
	fscanf( fin, "%d", &n );

	x = dmallocv( n+1 );
	f = dmallocv( n+1 );

	fscanf( fin, "%lf %lf", &x[0], &f[0] );
	for( i = 1; i <= n; i++ )
	{
	    fscanf( fin, "%lf %lf", &x[i], &f[i] );
	    if( x[i-1] > x[i] )
	    {
			printf("Error en les dades\n");
		  	exit(1);
	    }
	}

	fclose( fin );

	difdiv( n, x, f );

	h = (x[n] - x[0])/M;

	fout = fopen( "out.res", "w" );

	for( i = 0; i < M; i++ )
		fprintf( fout, "%lf %lf\n", x[0] + i*h, horner( x[0] + i*h, n, x, f ) );

	fclose( fout );


	return 0;

}

void difdiv( int n, double *x, double *f )
{
	int i, k, j;

	for( k = 1; k < n; k++ )
		for( i = n-1; i >= k; i-- )
			f[i] = ( f[i]-f[i-1] )/( x[i]-x[i-k] );

	return;
}

double horner( double z, int n, double *x, double *f )
{
	int i;
	double pz;

	pz = f[n];
	for( i = n-1; i >= 0; i-- )
		pz = pz*(z-x[i]) + f[i];

	return pz;
}