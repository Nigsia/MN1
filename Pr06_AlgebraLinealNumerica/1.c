#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <math.h>

#define N 5
#define NUM_ITER 3

float** initMat(int);

int main(void)
{
	srand( time(NULL) );
	float **A, **AA, *x, det = 0, *b;
	double *r;
	int *p, i, j, k, iter;
		
	//	Reserva de memòria i assignació de dades.
	A = initMat(N);
	AA = initMat(N);
	b = (float)malloc( N * sizeof(float) );
	x = (float)malloc( N * sizeof(float) );
	y = (float)malloc( N * sizeof(float) );
	r = (double)malloc( N * sizeof(double) );
	p = (int)malloc( N * sizeof(int) );

	for( i = 0; i < N; i++ )
	{
		for( j = 0; j < N; j++ )
		{
			A[i][j] = (float)rand()/RAND_MAX;
			AA[i][j] = A[i][j];		
		}	
		b[i] = (float)rand()/RAND_MAX;
	}

	// Solucionem el sistema Ax=b usant PA = LU --> LUx = Pb

	det = lupp(N, A, p);

	if(det == 0 || fabs(det) < FLT_EPSILON)
	{
		printf("Determinant és zero\n");
		exit(1);
	}
	// Potser s'ha de fer bp (la funció solveLU potser no accepta la permutació).
	solveLU( N, A, b, x, p );
	
	// Hauriem d'imprimir la X per veure 

	// Millora iterativa
	double *rr;
	float *r, *z, norma;
	iter = 0;
	
	rr = (double)( N * sizeof(double));
	r = (float)malloc( N * sizeof(float) );
	z = (float)malloc( N * sizeof(float) );

	while( iter < MAX_ITER )
	{
		norma = 0;
		for( i = 0;  i < N; i++)
		{
			rr[i] = b[i];
			for( j = 0; j < N; j++) 
				rr[i] = rr[i]-AA[i][j]*x[j];
			r[i] = rr[i];
			norma = norma + r[i]*r[i];
		}

		norma = sqrt(norma);
		// printf norma_2
		resol(N, A, r, z, p);
		for( i = 0; i < N; i++ )
			x[i] = x[i]+z[i];
	}

	return 0;
}
