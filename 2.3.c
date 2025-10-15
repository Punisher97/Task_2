#include <stdio.h>

//итеративная версия
int fib_iter(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}
// рекурсивная версия
int fib_rec(int n){
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_rec(n-1) + fib_rec(n-2);
}

int main(void){
    int i;
    while (scanf("%d", &i) == 1){
        printf("%d\n", fib_iter(i));
        printf("%d\n", fib_rec(i));
    }
}

