#include <stdio.h>

int main(){
    double x;
    scanf("%lf", &x);
    
    double res = 0.0;
    double coef;

    while (scanf("%lf", &coef) == 1) {
        res = res*x + coef;
    }
    printf("%lf", res);
}
