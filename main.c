#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "func.h"
// функция находит абсциссу точки пересечения двух функций на определенном интервале методом деления отрезка пополам
float root(float (f)(float), float (g)(float), float a, float b, float eps1) {
    float fa = f(a), fb = f(b), ga = g(a), gb = g(b);
    float c, fc, gc;
    int count = 0;
    while (b - a > eps1) {
        c = (a + b) / 2;
        fc = f(c);
        gc = g(c);
        if ((fa - ga) * (fc - gc) <= 0) {
            b = c;
            fb = fc;
            gb = gc;
            count++;
        } else {
            a = c;
            fa = fc;
            ga = gc;
            count++;
        }
    }
    printf("Count of iterations: %d  \t Root: %.3f\n", count, (a+b)/2);
    return (a + b) / 2;
}
// Функция находит значение определенного интеграла методом трапеций от функции на определенном отрезке
float integral(float (f)(float x), float a, float b, float eps2){
    float n = 1/eps2;
    float result = 0.0;
    float delta;

    delta = (b - a) / (float) n;

    int i;
    result += (f(a) + f(b)) * delta / 2;
    for (i = 1; i < n; ++i){
        result += f(a + i * delta) * delta;
    }
    return result;
}
// Функция выполняет основную задачу - поиск площади фигуры, ограниченной кривыми
void mtask(float a1, float b1, float a2, float b2, float a3, float b3, float eps1, float eps2){
    float root1, root2, root3, S;
    printf("f1 and f3: \t");
    root1 = root(f1, f3, a1, b1, eps1);
    printf("f2 and f3: \t");
    root2 = root(f3, f2, a2, b2, eps1);
    printf("f1 and f2: \t");
    root3 = root(f1, f2, a3, b3, eps1);
    S = integral(f1, root1, root3, eps2) - integral(f2, root2, root3, eps2) - integral(f3, root1, root2, eps2);
    printf("\n");
    printf("The area of the figure: %.3f\n", S);
}
// Функция, опиcывающая действия программы, при ключе -h (help - список доступных ключей)
void print_h(){
    printf("==============================HELP==============================\n"
           "Here is the list of keys you can use.\n"
           "1) Use key -f to look at functions;\n"
           "2) Use key -i (num of func) (a) (b) to find Riemann's integral on [a, b];\n"
           "3) Use key -m to look at main task solution;\n"
           "================================================================\n");
}
// Функция, опиcывающая действия программы, при ключе -f (список функций)
void print_f(){
    printf("==============================FUNC==============================\n"
           "1) exp(x)+2\n"
           "2) -1/x\n"
           "3) -2(x+1)/3\n"
           "================================================================\n");
}
// Функция, опиcывающая действия программы, при ключе -i (Нахождение интеграла от определенных функций на заданном пользователем интервале)
void i_a_to_b(char num, float a, float b, float eps2){
    switch (num) {
        case '1':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f1, a, b, eps2));
            break;
        case '2':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f2, a, b, eps2));
            break;
        case '3':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f3, a, b, eps2));
            break;
        default: break;
    }
}
int main(int argc, char * argv[]){
    int rez = 0;
    char num;
    float a, b;
    float eps = 0.001;
    float  eps1 = eps/2;
    float  eps2 = eps/100;
    float a1 = - 5, b1 = -3, a2 = -2, b2 = -1, a3 = -0.5, b3 = -0.1;
    while((rez = getopt(argc, argv, "hftmi:"))!= - 1){
        switch (rez) {
            case 'h' :
                print_h();
                break;
            case 'f':
                print_f();
                break;
            case 'i':
                num = (char)argv[optind-1][0];
                a = (float)atof(argv[optind]);
                b = (float)atof(argv[++optind]);
                i_a_to_b(num, a, b, eps2);
                break;
            case 'm':
                mtask(a1, b1, a2, b2, a3, b3, eps1, eps2);
                break;
            default: break;
        }

    }
    return 0;
}
