#include <stdio.h>

int main(void)
{
  
  int j, i = 0, i2 = 0;


  printf("Potencies de 10:\n");
  i = 0;
  for(j = 2; j < 15; j++)
  {
      i = i*10;
      printf("10^%d = %d\n",j, i);
  }
  
  printf("\nPotencies de 2:\n");
  i = 2;
  for(j = 2; j < 50; j++)
  {
      i = i*2;
      printf("2^%d = %d\n",j, i);
  }

  i = 0;
  i2 = -1;
  printf("\nSumarem fins que no poguem sumar més\n");
  while( i > i2 )
  {
  	printf("%d, ", i++);
  	i2++;
  }
  	
  i = 0;
  i2 = 1;
  printf("\nRestarem fins que no poguem restar més\n");
  while( i < i2 )
  {
  	printf("%d, ", i--);
  	i2--;
  }

  return 0;
  
}