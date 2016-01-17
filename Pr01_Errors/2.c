#include <stdio.h>

int main(void)
{
    float x;
    double y;
    
    scanf("%f", &x);
    printf("%.30f\n", x);
    
    scanf("%lf", &y);
    printf("%.30lf\n", y);
    
    return 0;
    
}