#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <math.h>

/************************************************************************************************/
/*								 		Memory allocation 										*/
/************************************************************************************************/

/**
 *	Allocates memory for an nxn-dimensional matrix of type double.
 *
 *  @args:
 *		- int: Dimension of the matrix.
 *	@return: an n x n matrix of type double.
 */
double**	dmallocm 			( int n );
/**
 *	Allocates memory for an n-dimensional vector of type double.
 *
 *  @args:
 *		- int: Dimension of the vector.
 *	@return: an n-dimensional vector of type double.
 */
double*		dmallocv 			( int n );
/**
 *	Allocates memory for an nxn-dimensional matrix of type int.
 *
 *  @args:
 *		- int: Dimension of the matrix.
 *	@return: an n x n matrix of type int.
 */
int**		imallocm			( int n ); 
/**
 *	Allocates memory for an n-dimensional vector of type int.
 *
 *  @args:
 *		- int: Dimension of the vector
 *	@return: an n-dimensional vector of type int.
 */
int*		imallocv 			( int n );

/**
 *	Frees the memory of an nxn-dimensional matix of type double.
 *
 *  @args:
 *		- double**:	The matrix.
 *		- int: 		Dimension of the matrix.
 */
void		dfreem				( double**,	int n );
/**
 *	Frees the memory of an nxn-dimensional matix of type int.
 *
 *  @args:
 *		- int**:	The matrix.
 *		- int: 		Dimension of the matrix.
 */
void 		ifreem				( int**, 	int n );

/************************************************************************************************/
/*								Matrix & vector initialization									*/
/************************************************************************************************/
/* TODO: File / manual input */

/**
 *	Allocates and fills an nxn-dimensional Identity matrix (Id is an identity matrix iff (Id_{i,j} = 1 iff i=j) ).
 *
 *  @args:
 *		- int: 		Dimension of the matrix.
 *	@return: An nxn-dimensional Identity matrix.
 */
double** 	identity_matrix		( int n );
/**
 *	Allocates and fills an nxn-dimensional matrix with random double numbers contained in an interval [min, max].
 *
 *  @args:
 *		- int: 		Dimension of the matrix.
 *		- double:	The minimum value.
 * 		- double:	The maximum value.
 *	@return: An nxn-dimensional matrix with random double values.
 */
double**	drandom_matrix		( int n, 	double min,		double max );
/**
 *	Allocates and fills an nxn-dimensional matrix with random integer numbers contained in an interval [min, max].
 *
 *  @args:
 *		- int: 		Dimension of the matrix.
 *		- int:		The minimum value.
 * 		- int:		The maximum value.
 *	@return: An nxn-dimensional matrix with random integer values.
 */
int**		irandom_matrix		( int n, 	int min,	int max );	
/**
 *	Allocates and fills the j-th n-dimensional vector from the 'natural' basis. (That is e_j = (0,..,0,1,0,...,0), where 1 is in the j-th position) .
 *
 *  @args:
 *		- int: 		Dimension of the vector.
 *		- u int:	The position for the 1.
 *	@return: The j-th n-dimensional vector from the 'natural' basis.
 */
double*		natural_base_vec	( int n, 	unsigned int j );
/**
 *	Allocates and fills an n-dimensional vector with random double numbers contained in an interval [min, max].
 *
 *  @args:
 *		- int: 		Dimension of the vector.
 *		- double:	The minimum value.
 * 		- double:	The maximum value.
 *	@return: An n-dimensional vector with random double values.
 */
double*		drandom_vector		( int n, 	double min,		double max );
/**
 *	Allocates and fills an n-dimensional vector with random integer numbers contained in an interval [min, max].
 *
 *  @args:
 *		- int: 		Dimension of the vector.
 *		- min:		The minimum value.
 * 		- min:		The maximum value.
 *	@return: An n-dimensional vector with random integer values.
 */
int* 		irandom_vector		( int n,	int min,	int max );

/************************************************************************************************/
/*							Printing & File Handling											*/
/************************************************************************************************/
/*  TODO: File printing & printLU */

/**
 *	Displays a given message and exits the program with an error code 1.
 *
 *  @args:
 *		- char*: 	A message to display.
 */
void 		printe		( char* );
/**
 *	Prints an nxn-dimensional matrix with double values.
 *
 *  @args:
 *		- double**: 	The matrix to print.
 *		- int:			Dimension of the matrix.
 */
void		dprintm		( double**, 	int n );
/**
 *	Prints an nxn-dimensional matrix with integer values.
 *
 *  @args:
 *		- int**: 		The matrix to print.
 *		- int:			Dimension of the matrix.
 */
void 		iprintm		( int**, 		int n );
/**
 *	Prints an n-dimensional vector with double values.
 *
 *  @args:
 *		- double*: 		The vector to print.
 *		- int:			Dimension of the vector.
 */
void 		dprintv		( double*, 		int n );
/**
 *	Prints an n-dimensional vector with integer values.
 *
 *  @args:
 *		- int*: 		The vector to print.
 *		- int:			Dimension of the vector.
 */
void 		iprintv		( int*, 		int n );
/**
 *	Prints on a file an nxn-dimensional matrix with double values.
 *
 *  @args:
 *		- double**: 	The matrix to print.
 *		- FILE*:		The file where we want to print the information.
 *		- int:			Dimension of the matrix.
 */
void		fdprintm	( double**, 	FILE*,		int n );
/**
 *	Prints on a file an nxn-dimensional matrix with integer values.
 *
 *  @args:
 *		- int**: 		The matrix to print.
 *		- FILE*:		The file where we want to print the information.
 *		- int:			Dimension of the matrix.
 */
void 		fiprintm	( int**, 		FILE*,		int n );
/**
 *	Prints on a file an n-dimensional vector with double values.
 *
 *  @args:
 *		- double*: 		The vector to print.
 *		- FILE*:		The file where we want to print the information.
 *		- int:			Dimension of the vector.
 */
void 		fdprintv	( double*,		FILE*, 		int n );
/**
 *	Prints on a file an n-dimensional vector with integer values.
 *
 *  @args:
 *		- int*: 		The vector to print.
 *		- FILE*:		The file where we want to print the information.
 *		- int:			Dimension of the vector.
 */
void 		fiprintv	( int*, 		FILE*,		int n );
/**
 *	Prints the permutation vector, L lower-triangular matrix with ones on the diagonal, U upper-triangular matrix, the matrix LU and the product L*U.
 *
 *  @args:
 *		- double**: 	The matrix LU.
 *		- int*:			The permutation vector.
 *		- int:			Dimension of the matrix and the permutation vector.
 */
void		printPALU	( double**, 	int*,		int );
/** 
 * 	Prints L lower-triangular matrix with ones on the diagonal, U upper-triangular matrix, the matrix LU and the product L*U.
 *
 *	@args:
 *		- double**:		The matrix LU.
 *		- int:			The dimension of the matrix.
 */
void		printLU 	( double**,		int );
/**
 *	Prints on a file the permutation vector, L lower-triangular matrix with ones on the diagonal, U upper-triangular matrix, the matrix LU and the product L*U.
 *
 *  @args:
 *		- double**: 	The matrix LU.
 *		- int*:			The permutation vector.
 *		- int:			Dimension of the matrix and the permutation vector.
 */
void		fprintPALU	( double**, 	int*,		FILE*,		int );
/** 
 * 	Prints on a file L lower-triangular matrix with ones on the diagonal, U upper-triangular matrix, the matrix LU and the product L*U.
 *
 *	@args:
 *		- double**:		The matrix LU.
 *		- int:			The dimension of the matrix.
 */
void		fprintLU 	( double**,		FILE*,		int );
/**
 *	Opens the FILE* f as an input file, with the name of the file you're working in. Ex: If you're working on foo.c, the in file would be foo.in.
 */
#define 	OPEN_IN_FILE(f)		file_open(&f, __FILE__, 0)
/**
 *	Opens the FILE** f as an output file, with the name of the file you're working in. Ex: If you're working on foo.c, the out file would be foo.out.
 */
#define 	OPEN_OUT_FILE(f)	file_open(&f, __FILE__, 1)

/**
 *	Used with definitions OPEN_IN_FILE & OPEN_OUT_FILE. Opens a file passed by reference, with the name of the file you're working in.
 * 
 *	@args:
 *		- FILE**:	The adress of the file you want to open.
 *		- char*:	The name that you want to give your file. The file will be named "name.in" or "name.out" depending on the inout parameter.
 *		- int:		This determines whether it is an input or an output file. inout==0 means in file. inout>0 means out file.
 */
void 		file_open	( FILE**, const char* , int inout );

/************************************************************************************************/
/*									Matrix Operations											*/
/************************************************************************************************/

/**
 *	Calculates the LU factorization.
 *
 *  @args:
 *		- double**: 	The matrix A we want to factorize.
 *		- int:			Dimension of the matrix.
 *	@return: The determinant of the matrix A.
 */
double		LU_factorization	( double**, 	int );
/**
 *	Calculates the LU factorization with permutation.
 *
 *  @args:
 *		- double**: 	The matrix A we want to factorize.
 *		- int*:			The permutation vector.
 *		- int:			Dimension of the matrix and the permutation vector.
 *	@return: The determinant of the matrix A.
 */
double		PALU_factorization	( double**, 	int*, 		int );
/**
 *	Calculates the product L*U.
 *
 *  @args:
 *		- double**: 	The matrix LU.
 *		- int:			Dimension of the matrix.
 *	@return: The product L*U = A.
 */
double**	LU_product			( double**, 	int );
/**
 *	Calculates the infinity norm (foreach row sum all elements in absolute value. Pick the maximum).
 *
 *  @args:
 *		- double**: 	The matrix A.
 *		- int:			Dimension of the matrix.
 *	@return: The infinity norm.
 */
double 		infinity_norm		( double**, 	int );
/**
 *	Solves the linear system LUx = b.
 *
 *  @args:
 *		- double**: 	The matrix LU.
 *		- double*:		The vector b
 *		- int:			Dimension of the matrix and the vector b.
 */
void		solve_LUx			( double**,		double*, 	int );
/**
 *	Solves the linear system PLUx = b. (That is for matrices that need PA=LU instead of regular LU)
 *
 *  @args:
 *		- double**: 	The matrix LU.
 *		- double*:		The vector b
 *		- int*:			The permutation vector.
 *		- int:			Dimension of the matrix, the vector b and the permutation vector.
 */
void 		solve_PLUx			( double**, 	double*,	int*, 	int );
/**
 *	Solves the linear system Lx = b.
 *
 *  @args:
 *		- double**: 	The matrix L.
 *		- double*:		The vector b.
 *		- int:			Dimension of the matrix and the vector b.
 */
void 		triinf				( double**,		double*,	int );
/**
 *	Solves the linear system Ux = b.
 *
 *  @args:
 *		- double**: 	The matrix U.
 *		- double*:		The vector b.
 *		- int:			Dimension of the matrix and the vector b.
 */
void 		trisup				( double**,		double*,	int );	
/**
 *	Permutes the vector b given the permutation vector.
 *
 *  @args:
 *		- double*:		The vector b.
 *		- int*:			The permutation vector.
 *		- int:			Dimension of the vector b and the permutation vector.
 */
void 		permute_b			( double*,		int*,		int );	
/**
 *	Calculates the inverse of a matrix A solving n linear systems Ax = Id[i].
 *
 *  @args:
 *		- double**: 	The matrix A.
 *		- int:			Dimension of the matrix.
 */
double**	inverese			( double**,   	int);
/**
 *	Sums two matrices of the same dimension.
 *
 *  @args:
 *		- double**: 	The first matrix.
 *		- double**:		The second matrix.
 *		- int:			Dimension of the matrices.
 */
double**	sum					( double**,		double**,	int );
/**
 *	Multiplies two matrices of the same dimension.
 *
 *  @args:
 *		- double**: 	The first matrix.
 *		- double**:		The second matrix.
 *		- int:			Dimension of the matrices.
 */
double**	product 			( double**, 	double**,   int );

/************************************************************************************************/
/*							Polynomial Operations / Interpolation								*/
/************************************************************************************************/
/**
 *	Evaluates the polynomial using the basis (x-x_i).
 *
 *  @args:
 *		- double: 		The point where we want to evaluate the polynomial.
 *		- int:			Degree of the polynomial.
 *		- double*:		The x_i values.
 *		- double*:		The values of the polynomial evaluated at every x_i.
 *
 *	@return: The value of the polynomial evaluated at the point. 
 */
double 		horner		( double,	int, 		double*, 	double* );
/**
 *	Evaluates the polynomial and it's derivative using the basis (x-x_i)
 *  @args:
 *		- double: 		The point where we want to evaluate the polynomial.
 *		- int:			Degree of the polynomial.
 *		- double*:		The x_i values.
 *		- double*:		The values of the polynomial evaluated at every x_i.
 *		- double p[2]:	A vector that will contain the solution for the evaluations (0 is the polynomial and 1 it's derivative).
 */
void 		hornered	( double,	int,		double*,	double*,	double[2] ); 
/**
 *	Calculates the coefficients of the interpolating polynomial using the divided differences method.
 *
 *	@args:
 *		- int: 			Degree of the polynomial.
 *		- double*:		The X vector.
 *		- double*:		The f(X) vector
 */
void  		diffiv		( int, 		double*, 	double* );
/**
 *	Creates a vector of points based on different methods.
 *	@args:
 *		- int: 			The method that should be used:
 *							1. Equidistant points,
 *							2. Chebyshev points.
 *							3. Random (different) points.
 *		- int: 			Number of points.
 *		- double:		The lower bound for the points.
 *		- double:		The upper bound for the points. 
 *		- double*:		The vector of poitns that will be filled.
 */
void 		nodes		(int, 		int,  		double,		double, 	double* );

/************************************************************************************************/
/*										Integration												*/
/************************************************************************************************/

/**
 *  Integrates using the trapezoidal rule.
 *  @args:
 *  	- int:			Number of subintervals in which the interval is divided.
 *		- double:		Step (distance between each subinterval).
 *		- double:		Value of trap(n/2, h*2)
 *		- double:		The lower bound for the interval. 
 *
 */
double trap( int, double, double, double, double (*f)(double) );