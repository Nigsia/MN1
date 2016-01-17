#include "../mn.h"
#include <time.h>

int main(void)
{
	double **a, *b;
	int i, j, n;
	FILE *f;
	char strIn[256];


	printf("Doneu la dimensió de la matriu: ");
	scanf("%d", &n);

	a = mallocMat(n);
	b = mallocVec(n);

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

	for( i = 0; i < n; i++ )
		fscanf(f, "%lf", &b[i]);

	fclose(f);

	for( i = 0; i < n; i++ )
		if(a[i][i] == 0)
		{
			printf("Matriu U Singular!\n");
			exit(1);
		}

	for ( i = 0; i < n; i++ )
		for( j = i + 1; j < n; j++ )
			b[j] = b[j] - a[j][i] * b[i];

	for ( i = n - 1; i >= 0; i-- ) 
	{
		b[i] = b[i] / a[i][i];
		for( j = i - 1; j >= 0 ; j-- )
			b[j] = b[j] - b[i] * a[j][i];
	}

	f = fopen("2.res", "w");
	if( f == NULL )
		printf("caca");

	for( i = 0; i < n; i++ )
	{
		fprintf(f, "%lf\t", b[i]);
	}	
	fprintf(f, "\n");

	fclose(f);

	return 0;
}
