#include <stdio.h>
#include <math.h>

#define EPSILON 1.e-15
#define N 4

double sh1(double);
double sh2(double);
double sh3(double);

int main(void)
{
	double r1, r2, r3, x;
	int i;

	x = 10.0*10.0*10.0;

	printf("10^i\tsh1\t\tsh2\t\tsh3\t\terr(sh2)\terr(sh3)\n");

	for(i = 2; i > -N; i--)
	{
		x /= 10.0;
		r1 = sh1(x);
		r2 = sh2(x);
		r3 = sh3(x);
		printf("10^%d\t%e\t%e\t%e\t%e\t%e\n", i, r1, r2, r3, (r1-r2)/r1, (r1-r3)/r1);
	}

	return 0;
}

double sh1(double x)
{
	return sinh(x);
}
double sh2(double x)
{
	return (exp(x)-exp(-x))/2.0;
}
double sh3(double x)
{
	double xn_1 = 0, xn = 0;
	int i = 1;

	xn = x;
	do
	{
		xn_1 = xn;
		xn += xn_1 * (x*x) / ((i+1)*(i+2));
		i += 2;
	}while(fabs(xn-xn_1) < EPSILON);

	return xn;
}