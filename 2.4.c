#include <stdio.h>

double str2double(char str[]){
    int i = 0, sign = 1;
    double val = 0.0, frac = 1.0;
    int exp_sign = 1, exp_val = 0;

    while (str[i] == ' ' || str[i] == '\t') i++;

    if (str[i] == '-')
    {sign = -1,
        i++;}
    else if (str[i] == '+')
        i++;

    //обработка целой части
    while (str[i] >='0' && str[i] <= '9'){
        val = val * 10.0 + (str[i] - '0');
        i++;
    }

    //дробная часть
    if (str[i] == '.'){
        i++;
        while (str[i] >= '0' && str[i] <= '9'){
            val = val * 10.0 + (str[i] - '0');
            frac *= 10.0;
            i++;
        }
    }

    val = sign * val / frac;

    //экспонента
    if (str[i] == 'e' || str[i] == 'E'){
        i++;
        if (str[i] == '-'){exp_sign = -1; i++;}
        else if (str[i] == '+') i++;

        while (str[i] >= '0' && str[i] <= '9'){
            exp_val = exp_val*10 + (str[i] - '0');
            i++;
        }

        double  power = 1.0;
        for (int j = 0; j < exp_val; j++)
            power *= 10.0;
       

        if (exp_sign == -1)
            val /= power;
        else
            val *= power;
    }

    return val;
}

int main(void){
    char s[100];
    while (scanf("%99s", s) == 1){
        double x = str2double(s);
        printf("%.10g", x);
    }
}


