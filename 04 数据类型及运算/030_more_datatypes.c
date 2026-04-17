/*
题目：
1.声明两个float类型变量float_1和float_2，并分别赋值为11.27和11.12345678910，
分别打印float_1和float_2。
2.声明一个double类型变量double_1并赋值为11.12345678910，分别打印float_2和double_1，
要求保留10位小数。

打印格式：变量名：值，例如，int1：80。
*/
#include <stdio.h>

int main()
{
    float float_1 = 11.27;
    float float_2 = 11.12345678910;
    printf("float_1: %f\n", float_1);
    printf("float_2: %f\n", float_2);
    double double_1 = 11.12345678910;
    printf("float_2: %.10f\n", float_2);
    printf("double_1: %.10lf\n", double_1);
}