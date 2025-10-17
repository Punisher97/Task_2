#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <ctype.h>

jmp_buf begin;       // точка начала диалога с пользователем
char curlex;         // текущий символ
char *input;         // указатель на строку ввода
int pos;             // текущая позиция в строке

// функции разбора
void getlex(void);
int expr(void);    // сложение и вычитание
int add(void);     // умножение и деление
int mult(void);    // возведение в степень
int atom(void);    // цифра или скобки
void error(void);

// получение следующего символа
void getlex() {
    while (input[pos] == ' ' || input[pos] == '\t') pos++; // пропуск пробелов
    curlex = input[pos];   // текущий символ
}

// ошибка
void error(void) {
    printf("\nОШИБКА!\n");
    longjmp(begin, 1);
}

// expr: сложение и вычитание (левоассоциативно)
int expr() {
    int e = add();
    while (curlex == '+' || curlex == '-') {
        char op = curlex;
        pos++;
        getlex();
        int right = add();
        if (op == '+') e += right;
        else e -= right;
    }
    return e;
}

// add: умножение и деление (левоассоциативно)
int add() {
    int a = mult();
    while (curlex == '*' || curlex == '/') {
        char op = curlex;
        pos++;
        getlex();
        int right = mult();
        if (op == '*') a *= right;
        else {
            if (right == 0) error(); // деление на ноль
            a /= right;
        }
    }
    return a;
}

// mult: возведение в степень (правоассоциативно)
int mult() {
    int val = atom();
    if (curlex == '^') {
        pos++;
        getlex();
        int exp = mult();  // рекурсивный вызов для праваассоциативности
        if (exp < 0) error(); // отрицательная степень
        int base = val;
        val = 1;
        for (int i = 0; i < exp; i++) val *= base;
    }
    return val;
}

// atom: цифра или '(' expr ')'
int atom() {
    int val = 0;
    if (curlex >= '0' && curlex <= '9') {
        val = curlex - '0';
        pos++;
        getlex();
    } else if (curlex == '(') {
        pos++;
        getlex();
        val = expr();
        if (curlex != ')') error();
        pos++;
        getlex();
    } else error();
    return val;
}

// главный цикл программы
int main() {
    char buf[256];
    while (fgets(buf, sizeof(buf), stdin)) {
        input = buf;
        pos = 0;
        if (setjmp(begin)) continue; // при ошибке возвращаемся сюда
        getlex();
        int result = expr();
        if (curlex != '\n' && curlex != '\0') error();
        printf("%d\n", result);
    }
    return 0;
}
