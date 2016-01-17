#include "mn.h"

#define M 100

void nodes( int, int, double, double, double* );
void difdiv( int, double*, double* );
double hornerd( double, int, double*, double*, double[2] );

int main( void )
{
	int n, i, j, indic;
	double min, max, *x, *f, h, p[2];

//	scanf("%d", &n);
//	scanf("%d", &indic);
//	scanf("%lf %lf", &min, &max);
	
	n = 5;
	indic = 1;
	min = -5.0;
	max = 5.0;

	x = dmallocv( n+1 );
	f = dmallocv( n+1 );

	nodes( indic, n, min, max, x );

	for( i = 0; i <= n; i++ )
		f[i] =  pow(x[i], 2);

	difdiv( n, x, f );
	
	printf( "#z\tf(z)\tf'(z)\tp(z)\tp'(z)\n" );
	
	h = (max-min)/M;
	
	for( i = 0; i < M; i++ )
	{
		hornerd( min+i*h, n, x, f, p );
		printf( "%+.4lf\t%+.4lf\t%+.4lf\t%+.4lf\t%+.4lf\n", min+i*h, pow(min+i*h, 2), (min+i*h)*2, p[0], p[1] );
	}

	return 0;
}


void nodes( int indic, int n, double min, double max, double *x )
{
	int i, j;
	double h = 0;

	n++;

	switch( indic )
	{
		case 1:
			for( i = 0; i < n; i++ )
			{
				h = (max-min/(n-1));
				x[i] = min + h*i;
			}		
		break;
		case 2:
			for( i = 0; i < n; i++ )
			{
				x[i] = min + ( (max-min)/2 ) * cos( ( (2*i+1)*M_PI )/(2*n) + 1 ); 
			}
		break;
		case 3:
			srand( time( NULL ) );
			for( i = 0; i < n; i++ )
			{
				x[i] = ((double)rand()/RAND_MAX)*( max-min ) + min;
				for( j = 0; j < i; j++ )
					while( fabs( x[j] - x[i] ) < 1.e-6 )
						x[i] = ((double)rand()/RAND_MAX)*( max-min ) + min;
			}
		break;
	}
	
	return;
}

void difdiv( int n, double *x, double *f )
{
	int i, j;



	for (i = 1; i < n; i++){

		for (j = n; j >= i; j--){

			f[j] = (f[j] - f[j-1]) /(x[j] - x[j-i]); 

		}

	}
	return;
}

double hornerd( double z, int n, double *x, double *f, double p[2] )
{
	int i;

	p[0] = f[n];
	p[1] = 0;
	for( i = n-1; i >= 0; i-- )
	{
		p[1] = p[1]*(z-x[i]) + p[0];
		p[0] = p[0]*(z-x[i]) + f[i];
	}

	return;
}
