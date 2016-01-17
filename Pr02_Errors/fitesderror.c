#include <stdio.h>
#include <math.h>
#include <float.h>

#define N 10000

int main(void)
{
  int k, i = 0, ind;
  double t, s, h, x, err;
  
  h = 10*M_PI/N;
  for(i = 0; i <=N; i++)
  {
      x = i*h;
      
      s = 0.;
      t = 1.;
      k = 0;
      
      while(fabs(t) >= fabs(s)*FLT_EPSILON)
      {
	 s += t;
	 t = -t*x*x/((k+1)*(k+2));
	 k += 2;
      }
      err = (s - cos(x) / cos(x));
      ind = 0;
      if(fabs(err) > FLT_EPSILON)
	ind = 1;
      printf("%+le %+le %+le %d \n", x, s, err, ind);
  }
    
  return 0;
}