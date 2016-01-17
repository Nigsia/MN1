#include "../mn.h"

int main(void)
{
	int n, i, j;
	double normaA, normaB, ncondicio;
	double **a, **b, *x, *f;
	FILE *fin, *fout;

	OPEN_IN_FILE(fin);
	OPEN_OUT_FILE(fout);

	fscanf(fin, "%d" , &n );

	a = dmallocm( n+1 );
	b = dmallocm( n+1 );
	x = dmallocv( n+1 );
	f = dmallocv( n+1 );

	for( i = 0; i <= n; i++ )
		fscanf(fin, "%lf %lf", &x[i], &f[i]);

	for( i = 0; i <= n; i++ )
		for( j = 0; j <= n; j++ )
	  		a[i][j] = pow( x[i] , j );

	fprintf( fout ,"Matriu A:\n\n" );
	fdprintm ( a , fout, n+1 );

	normaA = infinity_norm( a, n+1 );
	fprintf( fout, "\n\nNorma infinit de A = %lf\n" , normaA );

	b = inverse( a, n+1 );
	fprintf( fout ,"\n\nMatriu A^{-1}\n\n" );
	fdprintm( b, fout, n+1 );

	normaB = infinity_norm( b, n+1 );
	fprintf( fout, "\n\nnorma infinit de A^{-1} = %lf\n\n" , normaB );
	ncondicio = normaA * normaB;
	fprintf( fout, "\nnombre de condicio = %lf\n\n" , ncondicio );

	if( !LU_factorization( a, n+1 ) )
		printe("La factorització no es pot fer ja que el determinant és zero o numèricament molt proper a zero");
	fprintf( fout ,"\n\nMatriu A factoritzada\n\n" );
	fdprintm( a, fout, n+1 );

	solve_LUx ( a, f, n+1 );
	fprintf( fout ,"\n\nCoeficients del polinomi interpolador:\n\n" );
	fdprintv( f, fout, n+1 );

	fclose( fin );
	fclose( fout );

	dfreem( a, n+1 );
	dfreem( b, n+1 );
	free( x );
	free( f );
	
	return 0;
}
