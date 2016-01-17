#include "../mn.h"

#define M 100

int main( void )
{
	int n, i = 0;
	double *x, *f;
	double z, h;
	FILE *fin, *fout;

	OPEN_IN_FILE( fin );
	OPEN_OUT_FILE( fout );

	fscanf( fin, "%d", &n );

	x = dmallocv( n+1 );
	f = dmallocv( n+1 );

	fscanf( fin, "%lf %lf", &x[0], &f[0] );
	for( i = 1; i <= n; i++ )
	{
	    fscanf( fin, "%lf %lf", &x[i], &f[i] );
	    if( x[i-1] > x[i] )
	    {
			printe("Error en les dades.");
	    }
	}

	difdiv( n+1, x, f );

	h = (x[n] - x[0])/M;

	for( i = 0; i <= M; i++ )
		fprintf( fout, "%lf %lf\n", x[0] + i*h, horner( x[0] + i*h, n, x, f ) );

	fclose( fout );
	fclose( fin );

	free( x );
	free( f );

	return 0;

}