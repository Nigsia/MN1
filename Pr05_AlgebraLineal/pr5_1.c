#include "../mn.h"
#include <math.h>
#include <float.h>

double 		lupp		(int, double**, int*);
void 		escriureLU	(int, double**, int*, FILE*);
double** 	LU 			(double**, int);
void  		resoldreLUx (int, double**, double*, int*);
void 		permutarB	(int, double*, int*);
void 		triinf 		(int, double**, double*);
void 		trisup 		(int, double**, double*);

int main(void)
{
	double **a, *b, det;
	int i, j, n, *p;
	FILE *f;
	char strIn[256];


	printf("Doneu la dimensió de la matriu: ");
	scanf("%d", &n);

	a = mallocMat(n);
	b = mallocVec(n);
	p = imallocVec(n);

	printf("Doneu el fitxer d'entrada: ");
	scanf("%s", strIn);

	f = fopen(strIn, "r");
	if( f == NULL )
	{
		printf("Fitxer no valid.\n");
		exit(1);
	}

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			fscanf(f, "%lf", &a[i][j]);
	fclose(f);

	for( i = 0; i < n; i++ )
		p[i] = i;

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			b[i] += a[i][j];

	det = lupp(n, a, p);
	if( det == 0 )
	{
		printf("El determinant és zero. No podem fer factoritzacio LU.\n");
		return 1;
	}

	f = fopen("2.res", "w");
	if( f == NULL )
		printf("caca");

	escriureLU(n, a, p, f);

	fprintf(f, "\n");
	fprintf(f, "Vector b:\n");
	
	for ( i = 0; i < n; i++ )
		fprintf(f, "%+.4lf   ", b[i]);

	fprintf(f, "\n\n");

	resoldreLUx(n, a, b, p);

	fprintf(f, "LUx=b, x:\n");
	for( i = 0; i < n; i++ )
		fprintf(f, "%+.4lf\t", b[i]);
	fprintf(f, "\n\n");

	fclose(f);

}

double lupp(int n, double **a, int *p)
{
	double det = 1, normaInf = 0, sum = 0, max = 0, aux = 0, *auxFiles;
	int e, i, j, index, k;

	// Norma infinit
	for( i = 0; i < n; i++ )
	{
		sum = 0;
		for( j = 0; j < n; j++ )
		{
			sum += fabs(a[i][j]);
		}

		if( sum > max )
			max = sum;
	}
	normaInf = max;

	// PA=LU
	for( e = 0; e < n; e++ )
	{
		// Mirem l'element d'ordre màxim per fer la permutació
		index = e;
		for( j = e+1; j < n; j++ )
		{
			index = (fabs(a[index][e]) < fabs(a[j][e]))?j:index;
		}

		// PETA
		if( a[index][e] < FLT_EPSILON*normaInf )
			return 0;

		
		if(index == e)
			det *= a[index][e];
		else
		{
			det *= -a[index][e];
			// Permutem les files 
			auxFiles = a[e];
			a[e] = a[index];
			a[index] = auxFiles;

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

void escriureLU(int n, double **a, int *p, FILE *f)
{
	double **b;
	int i, j;

	if(f == NULL)
	{
		printf("Obre el fitxer abans de passar-lo!\n");
		return;
	}

	fprintf(f, "Vector de permutacio:  ");
	for( i = 0; i < n; i++ )
		fprintf(f, "%d ", p[i]);
	fprintf(f, "\n\n");

	fprintf(f, "L: \n");
	for( i = 0; i < n; i++ )
	{
		
		for( j = 0; j < n; j++ )
		{
			if(j < i)
				fprintf(f, "%+.4lf\t", a[i][j]);
			else if(j == i)
				fprintf(f, "+1.0000\t");
			else
				fprintf(f, "+0.0000\t");
		}
		fprintf(f, "\n");
	}
	fprintf(f, "\n");

	fprintf(f, "U: \n");
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
		{
			if(j < i)
				fprintf(f, "+0.0000\t");
			else
				fprintf(f, "%+.4lf\t", a[i][j]);
		}
		fprintf(f, "\n");
	} 
	fprintf(f, "\n");

	fprintf(f, "LU:\n");
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf(f, "%+.4lf\t", a[i][j]);
		fprintf(f, "\n");
	}
	fprintf(f, "\n");

	b = LU(a, n);

	fprintf(f, "L*U:\n");
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf(f, "%+.4lf\t", b[i][j]);
		fprintf(f, "\n");
	}

	return;
}

double** LU(double** a, int n)
{
	double** b;
	int i ,j, k;

	b = mallocMat(n);

	for (i = 0; i < n; i++) 
		for (j = 0; j < n; j++) 
			for (k = 0; k <= (i < j ? i : j); k++)
				if (i == k) 
					b[i][j] += a[k][j];
				else
					b[i][j] += a[i][k] * a[k][j];
				
	return b;					
}

void  resoldreLUx (int n, double **a, double *b, int* p)
{
	permutarB(n, b, p);
	triinf(n,a,b);
	trisup(n,a,b);
}

void permutarB	(int n, double *b, int *p)
{
	int i;
	double *bb = (double*)malloc(n*sizeof(double));
	
	for( i = 0; i < n; i++ )
	{
		bb[i] = b[p[i]];
	}

	for( i = 0; i < n; i++ )
		b[i] = bb[i];
}

void trisup (int n, double **a, double *b)
{
	int i, j;

	//Metode de substitucio endarrere.
	b[n-1] = b[n-1] / a[n-1][n-1];
	for ( i = n-2; i >= 0; i-- )
	{
		for ( j = i+1; j < n; j++ ) 
		{
			b[i] = b[i] - a[i][j] * b[j];
		}
		b[i] = b[i]/a[i][i];
	}
	return;
}

//Cal saber que a la diagonal hi ha 1.
void triinf (int n, double **a, double *b)
{
	int i, j;

	//Metode de substitucio endarrere.
	for ( i = 1; i < n; i++ )
	{
		for ( j = i-1; j >= 0; j-- )
			b[i] -= a[i][j] * b[j];
	}
	return;
}