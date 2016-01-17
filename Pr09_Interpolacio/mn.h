#include "../mn_headers.h"

/****************************************************************************/
/*							MEMORY ALLOCATION								*/
/****************************************************************************/

double* dmallocv( int n )
{
	double *v;

	v = (double*)malloc(n*sizeof(double));
	if( v == NULL)
		printe( "Error al reservar espai per al vector!\n" );

	return v;
}

double** dmallocm( int n )
{
	double **a; 
	int i;

	a = ( double** )malloc( n*sizeof( double* ) );
	
	if( a == NULL )
		printe( "Error al reservar espai per la matriu!\n" );

	for( i = 0; i < n; i++ )
	{
		a[i] = ( double* )malloc( n*sizeof( double ) );
		if( a[i] == NULL )
			printe( "Error al reservar espai per la matriu!\n" );
	}

	return a;
}

int* imallocv( int n )
{
	int *v;

	v = (int*)malloc(n*sizeof(int));
	if( v == NULL)
		printe( "Error al reservar espai per al vector!\n" );

	return v;
}

int** imallocm( int n )
{
	int **a;
	int i;

	a = ( int** ) malloc( n*sizeof( int* ) );
	if( a == NULL )
		printe( "Error al reservar espai per a la matriu" );

	for( i = 0; i < n; i++ )
	{
		a[i] = ( int* )malloc( n*sizeof(int) );
		if( a[i] == NULL )
			printe( "Error al reservar espai per la matriu!\n" );
	}

	return a;
}

void dfreem( double **a, int n )
{
	int i;
	
	for( i = 0; i < n; i++ )
		free(a[i]);
	free(a);

	return;
}

void ifreem( int **a, int n )
{
	int i;
	
	for( i = 0; i < n; i++ )
		free(a[i]);
	free(a);

	return;	
}

/****************************************************************************/
/*						MATRIX & VECTOR CREATION							*/
/****************************************************************************/

double** identity_matrix( int n )
{
	int i;
	double **id;

	id = ( double** )malloc( n*sizeof( double* ) );
	
	if( id == NULL )
		printe( "Error al reservar espai per la matriu!\n" );

	for( i = 0; i < n; i++ )
	{
		id[i] = ( double* )calloc( n, sizeof( double ) );
		if( id[i] == NULL )
			printe( "Error al reservar espai per la matriu!\n" );
		id[i][i] = 1.0;
	}

	return id;
}

double** drandom_matrix( int n, double min, double max )
{
	int i, j;
	double **m;

	srand( time( NULL ) );

	m = dmallocm( n );

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			m[i][j] = ((double)rand()/RAND_MAX)*( max-min ) + min;

	return m;
}

int** irandom_matrix( int n, int min, int max )
{
	int i, j;
	int **m;

	srand( time( NULL ) );

	m = imallocm( n );

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			m[i][j] = (rand() % (max+1-min))+min;

	return m;
}	

double*	natural_base_vec( int n, unsigned int j )
{
	double *ej;

	if( j >= n )
		printe( "L'index donat no es correcte" );

	ej = ( double* )calloc( n, sizeof( double ) );
	if( ej == NULL )
		printe( "Error al reservar espai per al vector!" );

	ej[j] = 1.0;

	return ej;
}

double*	drandom_vector( int n, double min, double max)
{
	int i;
	double *v;

	srand( time( NULL ) );

	v = dmallocv( n );

	for( i = 0; i < n; i++ )
		v[i] = ((double)rand()/RAND_MAX)*( max-min ) + min;

	return v;

}

int* irandom_vector ( int n , int min, int max)
{
	int i; 
	int *v;

	srand( time( NULL ) );

	v = imallocv( n );

	for( i = 0; i < n; i++ )
		v[i] = (rand() % (max+1-min))+min;

	return v;
}

/****************************************************************************/
/*						PRINTING & FILE HANDLING							*/
/****************************************************************************/

void printe( char* c )
{
	printf( "%s\n", c );
	exit(1);
}

void dprintm( double** a, int n )
{
	int i, j;
	
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+.4lf\t ", a[i][j] );
		printf( "\n" );
	}
	
	return;
}

void iprintm( int** a, int n )
{
	int i, j;

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+d\t", a[i][j] );
		printf( "\n" );
	}	

	return;
}

void dprintv( double *a, int n )
{
	int i;

	for( i = 0; i < n; i++ )
		printf( "%+.4lf\t", a[i] );
	printf( "\n" );
	
	return;
}

void iprintv( int *a, int n )
{
	int i;

	for( i = 0; i < n; i++ )
		printf( "%+d\t", a[i] );
	printf( "\n" );
	
	return;
}

void fdprintm( double** a, FILE *f, int n )
{
	int i, j;
	
	if( f == NULL )
		printe("Obre el fitxer abans d'intentar imprimir!");

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+.4lf\t ", a[i][j] );
		fprintf( f, "\n" );
	}
	
	return;
}

void fiprintm( int** a, FILE *f, int n )
{
	int i, j;

	if( f == NULL )
		printe("Obre el fitxer abans d'intentar imprimir!");

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+d\t", a[i][j] );
		fprintf( f,"\n" );
	}	

	return;
}

void fdprintv( double *a, FILE *f, int n )
{
	int i;

	if( f == NULL )
		printe("Obre el fitxer abans d'intentar imprimir!");

	for( i = 0; i < n; i++ )
		fprintf( f, "%+.4lf\t", a[i] );
	fprintf( f, "\n" );
	
	return;
}

void fiprintv( int *a, FILE *f, int n )
{
	int i;

	if( f == NULL )
		printe("Obre el fitxer abans d'intentar imprimir!");

	for( i = 0; i < n; i++ )
		fprintf( f, "%+d\t", a[i] );
	fprintf( f, "\n" );
	
	return;
}


void printPALU( double **a, int *p, int n )
{
	double **LU;
	int i, j;

	printf( "Vector de permutacio: " );
	for( i = 0; i < n; i++ )
		printf( "%d ", p[i] );
	printf( "\n\n" );

	printf( "L: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				printf( "%+.4lf\t", a[i][j] );
			else if( j == i )
				printf( "+1.0000\t" );
			else
				printf( "+0.0000\t" );
		}
		printf( "\n" );
	}
	printf( "\n" );

	printf( "U: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				printf( "+0.0000\t" );
			else
				printf( "%+.4lf\t", a[i][j] );
		}
		printf( "\n" );
	} 
	printf( "\n" );

	printf( "LU:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+.4lf\t", a[i][j] );
		printf( "\n" );
	}
	printf( "\n" );

	LU = LU_product( a, n );

	printf( "L*U:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+.4lf\t", LU[i][j] );
		printf( "\n" );
	}

	return;
}

void printLU( double **a, int n )
{
	double **LU;
	int i, j;

	printf( "L: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				printf( "%+.4lf\t", a[i][j] );
			else if( j == i )
				printf( "+1.0000\t" );
			else
				printf( "+0.0000\t" );
		}
		printf( "\n" );
	}
	printf( "\n" );

	printf( "U: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				printf( "+0.0000\t" );
			else
				printf( "%+.4lf\t", a[i][j] );
		}
		printf( "\n" );
	} 
	printf( "\n" );

	printf( "LU:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+.4lf\t", a[i][j] );
		printf( "\n" );
	}
	printf( "\n" );

	LU = LU_product( a, n );

	printf( "L*U:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			printf( "%+.4lf\t", LU[i][j] );
		printf( "\n" );
	}

	return;
}

void fprintPALU( double **a, int *p, FILE *f, int n )
{
	double **LU;
	int i, j;

	fprintf( f, "Vector de permutacio: " );
	for( i = 0; i < n; i++ )
		fprintf( f, "%d ", p[i] );
	fprintf( f, "\n\n" );

	fprintf( f, "L: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				fprintf( f, "%+.4lf\t", a[i][j] );
			else if( j == i )
				fprintf( f, "+1.0000\t" );
			else
				fprintf( f, "+0.0000\t" );
		}
		fprintf( f, "\n" );
	}
	fprintf( f, "\n" );

	fprintf( f, "U: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				fprintf( f, "+0.0000\t" );
			else
				fprintf( f, "%+.4lf\t", a[i][j] );
		}
		fprintf( f, "\n" );
	} 
	fprintf( f, "\n" );

	fprintf( f, "LU:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+.4lf\t", a[i][j] );
		fprintf( f, "\n" );
	}
	fprintf( f, "\n" );

	LU = LU_product( a, n );

	fprintf( f, "L*U:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+.4lf\t", LU[i][j] );
		fprintf( f, "\n" );
	}

	return;
}

void fprintLU( double **a, FILE *f, int n )
{
	double **LU;
	int i, j;

	fprintf( f, "L: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				fprintf( f, "%+.4lf\t", a[i][j] );
			else if( j == i )
				fprintf( f, "+1.0000\t" );
			else
				fprintf( f, "+0.0000\t" );
		}
		fprintf( f, "\n" );
	}
	fprintf( f, "\n" );

	fprintf( f, "U: \n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if( j < i )
				fprintf( f, "+0.0000\t" );
			else
				fprintf( f, "%+.4lf\t", a[i][j] );
		}
		fprintf( f, "\n" );
	} 
	fprintf( f, "\n" );

	fprintf( f, "LU:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+.4lf\t", a[i][j] );
		fprintf( f, "\n" );
	}
	fprintf( f, "\n" );

	LU = LU_product( a, n );

	fprintf( f, "L*U:\n" );
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf( f, "%+.4lf\t", LU[i][j] );
		fprintf( f, "\n" );
	}

	return;
}

void file_open( FILE** f, const char* name, int inout )
{
	char* fname;
	int i = 0;
	unsigned long name_size = sizeof(name);

	if( inout )
	{
		fname = (char*)malloc( name_size+2 );

		do
		{
			fname[i] = name[i];
			i++;

		}while(name[i] != '.');

		fname[i] = '.';
		fname[i+1] = 'o'; fname[i+2] = 'u'; fname[i+3] = 't';
		fname[i+4] = '\0';
		
		*f = fopen( fname, "w" );
		if( *f == NULL )
			printe( "Fitxer de sortida nul!");
	}
	else
	{
		fname = (char*)malloc( name_size+1 );

		do
		{
			fname[i] = name[i];
			i++;

		}while(name[i] != '.');

		fname[i] = '.';
		fname[i+1] = 'i'; fname[i+2] = 'n';
		fname[i+3] = '\0';
	
		*f = fopen( fname, "w" );
		if( *f == NULL )
			printe( "Fitxer d'entrada nul!");
	}
}

/****************************************************************************/
/*							MATRIX OPERATIONS								*/
/****************************************************************************/

/*
 *		FACTORIZATION
 */
double LU_factorization ( double **a, int n)
{
	int e, i, k;
	double det = 1, normaInf;

	normaInf = infinity_norm( a, n );

 	for( e = 0; e < n; e++ )
	{
		det *= a[e][e];
		if( fabs( a[e][e] ) <= DBL_EPSILON*normaInf )
			printe( "Error: un element de la diagonal de la matriu és 0 o molt proxim numericament." );

		for( i = e+1; i < n; i++ )
		{
			a[i][e] /= a[e][e];

			for( k = e+1; k < n; k++ )
			{
				a[i][k] -= a[i][e]*a[e][k];
			}
		}
	}

	return det;
}

double PALU_factorization( double **a, int *p, int n )
{
	double det = 1, normaInf = 0, aux = 0, *aux_files;
	int e, i, j, index, k;

	normaInf = infinity_norm( a, n );

	for( e = 0; e < n; e++ )
	{
		index = e;
		for( j = e+1; j < n; j++ )
		{
			index = ( fabs( a[index][e] ) < fabs( a[j][e] ) ) ? j : index;
		}

		if( fabs( a[index][e] ) <= DBL_EPSILON*normaInf )
			printe( "Error: un element de la diagonal de la matriu és 0 o molt proxim numericament." );

		
		if( index == e )
			det *= a[index][e];
		else
		{
			det *= -a[index][e];

			aux_files = a[e];
			a[e] = a[index];
			a[index] = aux_files;

			aux = p[e];
			p[e] = p[index];
			p[index] = aux;
		}

		for( i = e+1; i < n; i++ )
		{
			a[i][e] /= a[e][e];

			for( k = e+1; k < n; k++ )
			{
				a[i][k] -= a[i][e]*a[e][k];
			}
		}
	}

	return det;
}

/*
 * 		PRODUCT AND NORMS
 */
double** LU_product( double **a, int n )
{
	double** b;
	int i ,j, k;

	b = dmallocm( n );

	for ( i = 0; i < n; i++ ) 
		for ( j = 0; j < n; j++ ) 
			for ( k = 0; k <= (i < j ? i : j); k++ )
				if ( i == k ) 
					b[i][j] += a[k][j];
				else
					b[i][j] += a[i][k] * a[k][j];
				
	return b;					
}

double infinity_norm( double **a, int n )
{
	double max = 0, sum = 0;
	int i, j;

	for( i = 0; i < n; i++ )
	{
		sum = 0;
		for( j = 0; j < n; j++ )
		{
			sum += fabs( a[i][j] );
		}

		max = sum > max ? sum : max;
	}

	return max;
}

/*
 *	LUx = b & PLUx = b
 */
void solve_LUx( double **a, double *b, int n )
{
	triinf( a, b, n );
	trisup( a, b, n );
	return;
}

void solve_PLUx( double **a, double *b, int *p, int n )
{
	permute_b( b, p, n );
	triinf( a, b, n );
	trisup( a, b, n );
	return;
}

void trisup( double **a, double *b, int n )
{
	int i, j;

	b[n-1] = b[n-1] / a[n-1][n-1];
	for ( i = n-2; i >= 0; i-- )
	{
		for ( j = i+1; j < n; j++ ) 
			b[i] = b[i] - a[i][j] * b[j];
		b[i] = b[i]/a[i][i];
	}
	return;
}

void triinf( double **a, double *b, int n )
{
	int i, j;

	for ( i = 1; i < n; i++ )
		for ( j = i-1; j >= 0; j-- )
			b[i] -= a[i][j] * b[j];

	return;
}

void permute_b( double *b, int *p, int n )
{
	int i;
	double *bb = ( double* )malloc( n*sizeof( double ) );
	
	for( i = 0; i < n; i++ )
	{
		bb[i] = b[p[i]];
	}

	for( i = 0; i < n; i++ )
		b[i] = bb[i];
}

/*
 *	Other Stuff
 */ 

double** inverse( double **a, int n )
{
 	double det, **a1, **id, temp;
 	int i, j;

 	a1 = dmallocm( n );

 	for ( i = 0; i < n; i++ )
 		for( j = 0; j < n; j++ )
 			a1[i][j] = a[i][j];

 	det = LU_factorization( a1, n );
	
	if( fabs( det ) <= DBL_EPSILON )
		printe( "Error: el determinant es zero o molt petit numericament." );

 	id = identity_matrix( n );

 	for( i = 0; i < n; i++ )
		solve_LUx( a, id[i], n );


	for( i = 0; i < n; i++ )
		for( j = 0; j < i; j++ )
		{
			temp = a1[i][j];
			a1[i][j] = a1[j][i];
			a1[j][i] = temp;
		}

	return a1;
}

double** sum( double **a, double **b, int n )
{
	int i, j;
	double** c;

	c = dmallocm( n );

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			c[i][j] = a[i][j]+b[i][j];

	return c;
}

double** product( double **a, double **b, int n )
{
	int i, j, k;
	double **c;

	c = dmallocm( n );

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			c[i][j] = 0;

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			for( k = 0; k < n; k++ )
				c[i][j] += a[k][j]*b[i][k];

	return c;
}


/* Matriu de hilbert

for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = (double) 1/(i + j + 1);
			b[i] += mat[i][j];
		}
	}
*/

/************************************************************************************************/
/*							POLYNOMIAL OPERATIONS / INTERPOLATION								*/
/************************************************************************************************/
