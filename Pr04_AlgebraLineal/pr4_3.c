#include "../mn.h"

int main (void)
{
	double **a, *x, *y;
	int i, j, n;
	FILE *f;
	char strIn[256];


	printf("Doneu la dimensió de la matriu: ");
	scanf("%d", &n);

	a = mallocMat(n);
	x = mallocVec(n);
	y = mallocVec(n);

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
		fscanf(f, "%lf", &x[i]);

	fclose(f);



	for( i = 0; i < n; i++ )
	{
		y[i] = 0;
		for( j = i; j < n; j++ )
			y[i] += a[i][j]*x[j];
	}

	for( i = 0; i < n; i++ )
	{
		x[i] = y[i];
		for( j = 0; j < i; j++ )
			x[i] += a[i][j]*y[j]; 
	}

	f = fopen("3.res", "w");
	if( f == NULL )
		printf("caca");

	for( i = 0; i < n; i++ )
	{
		fprintf(f, "%lf\t", x[i]);
	}	
	fprintf(f, "\n");

	fclose(f);

}