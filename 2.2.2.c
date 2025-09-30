  #include <stdio.h>

int main() {
    double x;
    scanf("%lf", &x);

    double polynom = 0.0;    
    double derivative = 0.0;   
    double coef;

    while (scanf("%lf", &coef) == 1) {
        derivative = derivative * x + polynom;
        polynom = polynom * x + coef;
    }
    
    printf("%lf\n", polynom);
    printf("%lf\n", derivative);
    
    return 0;
}
