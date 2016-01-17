/*
 *	x_1 = 1; 
 *	x_2 = 1-sqrt(3)
 *	x_n = 2(x_(n-1) + x_(n-2)) n>= 3. 
 *	Solució exacta z = (1-sqrt(3))^(n-1) 
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double x1, x2, x, z, errAbsN, errAbsN_1;
  int i;
  
  x1 = 1;
  x2 = 1-sqrt(3);
  z = (1-sqrt(3))*(1-sqrt(3));
  
  printf("n\tz\t\tx\t\tx-z\t\t(x-z)/z\t\teAbs_n/eAbs_(n-1) \n");
  
  errAbsN_1 = 1;
  
  for(i = 3; i <= 50; i++)
  {
    x = 2*(x2+x1);
    
    errAbsN = x-z;
    
    printf("%d\t%+.4e\t%e\t%e\t%e\t%e\n", i, z, x, x-z, (x-z)/z, errAbsN/errAbsN_1);
    
    z *= (1-sqrt(3));
    
    x1 = x2;
    x2 = x;
    
    errAbsN_1 = errAbsN;
    
  }
  
  return 0;
}