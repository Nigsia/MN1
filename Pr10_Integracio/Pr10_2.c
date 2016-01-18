#include "../mn.h"
#include "f.h"

#define MAX_FILES 50
#define PREC 1.e-5

int main( void )
{
	int n = 1, files = 0, i;
	double h, a, b, r, **m;
	FILE *fin, *fout;

	OPEN_IN_FILE( fin );
	OPEN_OUT_FILE( fout );

	fscanf( fin, "%lf %lf", &a, &b );

	m = dmallocm( MAX_FILES );

	h = b-a;
	m[0][0] = h*(f(b)-f(a))/2.0;

	do
	{
		files++;
		n = n*2.0;
		h = h/2.0;
		m[files][0] = trap( n, h, m[files-1][0], a, &f );

		for( i = 0; i < files; i++ )
			m[files][i+1] = ( pow(4, i+1)*m[files][i] - m[files-1][i] ) / ( pow(4, i+1) - 1 );

		r = fabs( m[files][i] - m[files][i-1] );
		fprintf( fout, "r_%d = %10lf\n", files, r );	

	}while( r > PREC && files+1 < MAX_FILES );

	if( r <= PREC )
		fprintf( fout, "Valor de la integral = %lf\n", m[files][i] );
	else
		fprintf( fout, "No ha convergit.\n" );

	return 0;
}
