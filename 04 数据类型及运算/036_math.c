/*
题目：
1、声明一个int类型变量result_1储存2+10/8*3，并打印出结果。
2、声明一个double类型变量result_2储存2+10/8.0*3，并打印出结果。
以上题目的打印格式：变量名 = 值。
3、写一个一元二次求根公式计算器
*/

#include <stdio.h>
#include <math.h>

int main() {
    int result_1 = 2 + 10 / 8 * 3;
    printf("result_1 = %d\n", result_1);

    double result_2 = 2 + 10 / 8.0 * 3;
    printf("result_2 = %lf\n", result_2);
    
    int a = 1;
    int b = 9;
    int c = 20;
    double delta = sqrt(pow(b,2) - 4 * a * c);
    double x_1 = (-b + delta) / 2 * a;
    double x_2 = (-b - delta) / 2 * a;
    printf("该一元二次方程式的根为：%lf,%lf", x_1, x_2);
}