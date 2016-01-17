#include "../mn.h"
#include <time.h>

double** LU(double**, int);

int main(void)
{
	double **a, **b;
	int i, j, k, n;
	FILE *f;
	char strIn[256];
	clock_t start, end;

	printf("Doneu la dimensio de la matriu: ");
	scanf("%d", &n);

	a = mallocMat(n);
	b = mallocMat(n);

	do
	{
		printf("1. Dades aleatories\n2. Fitxer\n");
		scanf("%d", &i);
	}while( i != 1 && i != 2 );

	// Aleatori
	if(i == 1)
	{
		srand(time(NULL));
		for( i = 0; i < n; i++ )
			for( j = 0; j < n; j++ )
				a[i][j] = rand()/RAND_MAX * 2 - 1;
	}
	else
	{
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
	}

	start = clock();

	for( i = 0; i < n; i++ )
	{	for( j = 0; j < n; j++ )
		{
			for( k = 0; k < i; k++ )
			{
				if( k <= j)
					b[i][j] += a[i][k]*a[k][j];
			}
			if( j >= i )
				b[i][j] += a[i][j];
		}
	}
	end = clock();
	printf("t\tn\tt/n\n%.4lf\t%d\t%lf\n", difftime(end, start)/CLOCKS_PER_SEC, n, n/difftime(end, start)/CLOCKS_PER_SEC);
	
	f = fopen("1.res", "w");
	if( f == NULL )
		printf("caca");

	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ )
			fprintf(f, "%lf\t", b[i][j]);
		fprintf(f, "\n");
	}	

	return 0;
}

double** LU_product(double** a, int n)
{
	double** b;
	int i ,j, k;

	B = mallocMat(n);

	for (i = 0; i < n; i++) 
		for (j = 0; j < n; j++) 
			for (k = 0; k <= (i < j ? i : j); k++)
				if (i == k) 
					b[i][j] += a[k][j];
				else
					b[i][j] += a[i][k] * a[k][j];
				
	return b;					
}
