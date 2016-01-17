#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOL 1.e-12

void printMat(double **mat, int n, int m);
void printVect(double *vect, int n);
void printVectint(int *vect, int n);
int palu (int n, double **A, int *p, double tol, int *cont);
double** matrixProduct(double** A, double** B, int n, int p, int m);
double** separateLU(double **mat, double **U, int n);
int triinf (int n, double **L, double *b, double tol);
int resol( int n, double **A, double *b, int *p);
int trisup (int n, double **U, double *b, double tol);
void permutarB(int *p, double *b, int n);
double detPALU(double **U, int n, int cont);
int tridiag(int n, double *p, double *q, double *r, double *y);

//En aquest cas volem resoldre un sistema mitjancant  l'eliminacio gaussiana amb pivotatge (PALU).

int main (void){

	int i, j, n, res, *p, cont = 0; 
	double *b, **mat, **L, **U;

	printf("Introdueix la dimensio desitjada \n");
	scanf(" %d", &n);

	//Control d'errors, si la dimensio es negativa o 0, hi ha un error. 
	if (n <= 0){
		printf("La dimensio introduida no es valida \n");
		exit(-1);
	}
	/** -----------------------------------------INICIALITZACIONS DELS VECTORS ----------------------------------------------------**/



	/**
	Guardam memoria per la matriu inicial que volem.
	Per la matriu U que despres necessitarem.
	Pel vector b de termes indepentents.
	Pel vector p que ens controla les permutacions
	**/




	//Guardam memoria primer per cada fila de la matriu i despres per cada columna. 
	mat = (double **)malloc(n*sizeof(double *));
	U = (double **)malloc(n*sizeof(double *));

	if (mat == NULL){
		printf("Error a l'assignar memoria de la matriu \n");
		exit(1);
	}

	if (U == NULL){
		printf("Error a l'assignar memoria \n");
	}
	
	for(i = 0; i < n; i++){
		mat[i] = (double *)malloc(n*sizeof(double));
		U[i] = (double *)malloc(n*sizeof(double));
		if (mat == NULL || U == NULL){
			printf("Error a l'assignar memoria de la matriu \n ");
			exit(1);
		}
	}
	
	//Guardam memoria per el vector de termes independents de la matriu. 
	p = (int *) malloc(n*sizeof(int));
	b = (double *)malloc(n*sizeof(double));
	if (p == NULL || b == NULL){
		printf("Error a l'assignar memoria del vector \n");
		exit(1);
	}

	//Inicialitzam els valors de b a 0.
	for (i = 0; i < n; i++){
		p[i] = i+1;
		b[i] = 0.0;
	}



	/** ---------------------------------------------------GENERACIO DE LA MATRIU I DELS TERMES INDEPENTENTS ------------------------------------------------ **/


	/*
	//Generacio de la matriu de Hilbert i del vector de termes independents: 
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			mat[i][j] = (double) 1/(i + j + 1);
			b[i] += mat[i][j];
		}
	}
	*/
	
	for(i = 0; i < n; i ++){
                printf("Introdueix els nombres de la fila \n");
                for (j = 0; j < n; j++){
                                scanf("%le", &mat[i][j]);
                }
        }

	
	//Generam una matriu la solucio del sistema de la qual sigui 1.
	for (i = 0; i < n; i++){
		b[i] = 0;
		for (j = 0; j < n; j++){
			b[i] += mat[i][j];
		}
	}

	printVect(b, n);

	/** ----------------------------------------------------OPERACIONS NECESSARIES DEL PROGRAMA ------------------------------------------ **/

	//Imprimim la matriu i el seu vector de termes independents per informar a l'usuari:
	//printf("Matriu generada: \n");
	//printMat(mat, n, n);

	//1. APLICAM ELIMINACIO GAUSSIANA AMB PIVOTATGE:

	//Resolem pel metode de palu. Si el resultat ens dona -1 vol dir que hem fet algun error. Sortim. 
	res = palu(n, mat, p, TOL, &cont);
	if (res == -1){
		exit(-1);
	}



	//2. COMPROVACIO DE QUE L'ELIMINACIO GAUSSIANA HA FUNCIONAT CORRECTAMENT:

	printf("Matriu obtinguda despres d'haver fet el metode PALU \n");
	printMat(mat, n, n);
	printf("Vector de trasposicions \n");
	printVectint(p, n);

	//3. CONTROL DE QUANTES PERMUTACIONS HEM FET:
	printf("Hem fet %d permutacions \n", cont);


	//4. SEPARAM LES MATRIUS L i U PER PODER CALCULAR EL DETERMINANT:
	L = separateLU(mat, U, n);
	//printf("La matriu L queda: \n");
	//printMat(L, n, n);
	//printf("La matriu U queda: \n");
	//printMat(U, n, n);
	printf("El determinant de la matriu es %le \n", detPALU(U, n, cont));


	//5: RESOLEM EL SISTEMA SEGONS ELS TERMES INDEPENTENTS b I LA MATRIU QUE ENS HAVIEN DONAT (ara modificada):
	res = resol(n, mat, b, p);
	//Si el resultat es > 0 hem d'acabar perque vol dir que hi ha hagut algun problema 
	if (res > 0){
		exit(1);
	}

	//6. DONAM LA SOLUCIO DEL SISTEMA:
	printf("Vector solucio del sistema: \n");
	printVect(b, n);


	//printf("Matriu resultat de multiplicar L * U \n");
	//printMat(matrixProduct(L, U, n, n, n), n, n);



	/** -------------------------------------------- OPERACIONS D'ALLIBERACIO DE MEMORIA ----------------------------------- **/
	
	//Alliberam memoria.
	free(p);
	free(b);
	for (i = 0; i < n; i++){
		free(mat[i]);
	}
	free(mat);

	return 0;
}



/** ELIMINACIO GAUSSIANA AMB PIVOTATGE, CONTROL DE LES PERMUTACIONS **/
//A mes de fer l'eliminacio gaussiana, imprimim en cada pas quines permutacions anem fent i comptem quantes n'hem fet en total.

int palu (int n, double **A, int *p, double tol, int *cont){

		int i, k, j, auxp, max;
		double *aux;

	//Hem de fer pivotatge parcial, per tant, hem de buscar el maxim.
	for (k = 0; k < n - 1; k++){
		//Per defecte, el maxim sera el primer element. A partir d'aqui comencam a buscar.
		max = k;
		for (i = k+1; i < n; i++){
			//Per a cada valor de i ens sona l'index que conte l'element maxim. 
			max = (fabs(A[max][k]) < fabs(A[i][k]))?i:max;
		}
		//Ara la i conte l'index de l'element maxim.
		//Si el maxim no es k, hem de canviar les files.
		if(max != k){
			*cont += 1;
			//Guardam la fila en una auxiliar i intercanviam.
			aux = A[k];
			A[k] = A[max];
			A[max] = aux;
			//Intercanviam tambe els elements del vector que ens controla les permutacions.
			auxp = p[k];
			p[k] = p[max];
			p[max] = auxp;
		}
		printf("Vector de permutacio en el pas k = %d \n", k);
		printVectint(p, n);

		//Continuam amb el metode de Gauss un cop obtingut l'element maxim.		
		for (i = k+1; i < n; i++){
			if (fabs(A[k][k]) < tol){
				printf("Estas dividint entre 0, l'algorisme no pot continuar \n");
				return -1;
			}
			A[i][k] = A[i][k] / A[k][k];
			for (j = k+1; j < n; j++){
				A[i][j] = A[i][j] - A[i][k] * A[k][j];
			}
		}
	}

	return 0;
}

/** ------------------------------ FUNCIONS PER IMPRIMIT MATRIUS, VECTORS I EL VECTOR DE PERMUTACIONS ---------------------------------- **/

void printMat(double **mat, int n, int m){
	int i, j;
	
	for (i = 0; i<n; i++){
		for (j = 0; j < m; j++){
			printf(" %20.16f", mat[i][j]);
		}
		printf("\n");
	}
}

void printVect(double *vect, int n){
	int i;
	for (i = 0; i < n; i++){
		printf(" %d %20.16f  \n", i+1, vect[i]);
	}
}

void printVectint(int *vect, int n){
	int i;
	for (i = 0; i < n; i++){
		printf(" %d %d  \n", i+1, vect[i]);
	}
}

/** ----------------------------------PRODUCTE DE MATRIUS ------------------------------- **/
//Retornam la matriu producte resultant.
//Si son matrius quadrades, totes les dimensions coincideixen.

double** matrixProduct(double** A, double** B, int n, int p, int m){
	int i, j; 
	double **C;
	
	//Generacio de la matriu auxiliar resultat del producte de matrius:
	C = (double **)malloc(n*sizeof(double *));

	if (C == NULL){
		printf("Error a l'assignar memoria de la matriu \n");
		exit(1);
	}
	
	for(i = 0; i < n; i++){
		C[i] = (double *)malloc(m*sizeof(double));
		if (C == NULL){
			printf("Error a l'assignar memoria de la matriu \n ");
			exit(1);
		}
	}

	//Producte de matrius:
	for (i = 0; i < n; i++){
		for (j = 0; j < m; j++){
			C[i][j] = 0;
			for (p = 0; p < n; p++){
				C[i][j] += A[i][p] * B[p][j];
			}
		}

	}

	return C;

}



/** ----------------------------- SEPARACIO DE LES MARIUS L i U A PARTIR DE LA MATRIU D'ELIMINACIO GAUSSIANA --------------------------- **/


//Com a parametre posam la matriu U que modificarem.
//Com que no podem retornar dues coses, una la passam com a variable i l'altre la retornam.
double ** separateLU(double **mat, double **U, int n){
	int i, j;
	double **L;

	//Generacio de la matriu que retornarem com a L.
	L = (double **)malloc(n*sizeof(double *));

	//Guardam memoria per la matriu L, la que retornarem.
	if (L == NULL){
		printf("Error a l'assignar memoria de la matriu \n");
		exit(1);
	}
	
	for(i = 0; i < n; i++){
		L[i] = (double *)malloc(n*sizeof(double));
		if (L == NULL){
			printf("Error a l'assignar memoria de la matriu \n ");
			exit(1);
		}
	}

	//Omplim les dues matrius amb els elements corresponents.
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			//Els elements de sobre de la diagonal corresponen al elements de la matriu U.
			//Per a la matriu L, els elements de sobre la diagonal son 0.
			if (i < j){
				L[i][j] = 0.0;
				U[i][j] = mat[i][j];
			//Els elements de la diagonal son 1 per a L.
			//Per a la matriu U son els elements de la matriu gaussiana.
			} else if (i == j){
				L[i][j] = 1.0;
				U[i][j] = mat[i][j];
			//Els elements de sota de la diagonal son els elements corresponents a la matriu L.
			//En canvi, son 0 per a U.
			} else {
				L[i][j] = mat[i][j];
				U[i][j] = 0.0;
			}
		}
	}

	return L;

}




/** ------------------------ RESOLUCIO DEL SISTEMA TENINT EN COMPTE QUE LA MATRIU HA TINGUT PERMUTACIONS ---------------------- **/
//Necessitam un metode trsup, un metode triinf, un metode per permutar el vector B i un metode per resoldre-ho tot conjunt. 


int trisup (int n, double **U, double *b, double tol){
	int i, j;
	for (i = 0; i < n; i++){
		if (fabs(U[i][i]) < tol){
			printf("Error en els elements de la diagonal: alguns son 0 \n");
			return 1;
		}
	}
	

	//Metode de substitucio endarrere.
	b[n-1] = b[n-1] / U[n-1][n-1];
	for (i = n-2; i >= 0; i --){
		for (j = i+1; j < n; j++){
			b[i] = b[i] - U[i][j] * b[j];
		}
		b[i] = b[i]/U[i][i];
	}
	printVect(b, n);
	printf("Calcul realitzat satisfactoriament \n");
	return 0;
}

//Cal saber que a la diagonal hi ha 1.
int triinf (int n, double **L, double *b, double tol){
	int i, j;
	for (i = 0; i < n; i++){
		if (fabs(L[i][i]) < tol){
			printf("Error en els elements de la diagonal: alguns son 0 \n");
			return 1;
		}
	}
	

	//Metode de substitucio endarrere.
	for (i = 1; i < n; i ++){
		for (j = i-1; j >= 0; j--){
			b[i] = b[i] - L[i][j] * b[j];
		}
	}
	printVect(b, n);
	printf("Calcul realitzat satisfactoriament \n");
	return 0;
}

int resol(int n, double **A, double *b, int *p){
	int res = 0;
	//Primer permutam el vector b.
	permutarB(p, b, n);

	//Despres resolem el sistema Lz = Pb
	res = triinf(n, A, b, TOL);
	//Despres resolem el sistema Ux = z
	res += trisup(n, A, b, TOL);

	//Si la funcio ens retorna un valor > 1 vol dir que haura fallat en alguna part dels algorismes anteriors.
	//Haurem de parar els algorismes.
	return res;

}

void permutarB(int *p, double *b, int n){
	int i, aux;
	double auxb;
	/*
	//Algorisme per permutar, miram cada posicio:
	for (i = 0; i < n; i++){
		//Fins que no haguem aconseguit colocar aquest index be:
		while (p[i] != i+1){
			//Guardam el valor que te actualment.
			aux = p[i];
			//Aixo vol dir que el valor que es troba en aquesta posicio es el que volem.
			p[i] = p[aux-1];
			//Reassignam.
			p[aux-1] = aux;

			//Fem els mateixos passos amb el vector b per intercanviar files segons les permutacions.
			auxb = b[i];
			b[i] = b[aux-1];
			b[aux-1] = auxb;
		}

	}
	*/
	double *bb; 
	bb = (double *)malloc(n*sizeof(double));
	for (i = 0; i < n; i++){
		bb[i] = b[p[i]-1];
	}
	 for (i = 0; i < n; i++){
                b[i] = bb[i];
        }
	free(bb);
	
}




/** ---------------------------- CALCUL DEL DETERMINANT TENINT EN COMPTE QUE HI HA HAGUT PERMUTACIONS A LA MATRIU ----------------------- **/



double detPALU(double **U, int n, int cont){
	int i = 0;
	double det = U[i][i];

	for (i = 1; i < n; i++){
		det *= U[i][i];
	}

	if (cont % 2 == 0){
		return det;
	} else {
		return (-1 * det);
	}
}

int tridiag(int n, double *p, double *q, double *r, double *y){
	int i; 

	for (i = 1; i < n; i++){
		r[i] = r[i] / p[i-1];
		p[i] = p[i] - r[i] * q[i-1];
		y[i] = y[i] - r[i] * y[i-1]; 
	}

	y[n-1] = y[n-1]/p[n-1];
	for (i = n-2; i >= 0; i--){
		y[i] = (y[i] - q[i]*y[i+1])/p[i];
	}

	return 0; 
}
