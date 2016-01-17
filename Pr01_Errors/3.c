/* Llista 1 exercici 3 */

#include <stdio.h>
#include <math.h>
#include <float.h>

#define a 1.0
#define b 8.0

int main(void)
{
  int n, i, ind;
  float x;
  double h, z, err;

  scanf("%d", &n);
  if(n<=0)
    return;

  printf("# FLT_EPSILON = %+.10e \n\n", FLT_EPSILON);

  h = (b-a)/n;

  for(i = 0; i <= n; i++)
  {
    z = a+i*h;
    x = z;
    err = (x-z)/z;

    ind = 0;
    if(fabs(err)>FLT_EPSILON)
      ind = 1;
    
    printf(" %+.3le %+.le %3d \n", z, err, ind);
  }
  return 0;
}