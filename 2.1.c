#include <stdio.h>


double calculation_sqrt(double x, double eps)
{
    double current, next;

    if (x == 0.0) return 0.0; //корень из нуля - ноль
    current = 1.0;

    while(1)
    {
        next = 0.5 * (current + x/current);

        if ((current - next < eps && current - next >=0) ||
            (next - current < eps && next - current >=0)) break;

        current = next;
    }
return next;
}

main()
{
    double eps, x, res;

    scanf("%lf", &eps);

    while (scanf("%lf", &x) == 1){
        if (x < 0) continue;
    res = calculation_sqrt(x, eps);
    printf("%.10g\n", res);
    }
}
