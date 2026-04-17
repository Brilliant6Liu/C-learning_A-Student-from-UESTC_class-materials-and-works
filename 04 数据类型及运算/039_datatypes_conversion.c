/*
题目：
1、定义一个int类型变量num_1，初始值为8。
2、定义一个char类型变量ch，初始值为e。
3、定义一个float类型变量num_2，初始值为1.23。
4、定义一个double类型变量num_3，初始值为4.98。
5、定义一个double类型变量result来储存计算结果。
6、将变量ch转换为double类型，并跟变量num_1相加，将结果赋值给变量result，并打印出结果。
7、将变量num_2和num_3相加的结果转换为int类型，赋值给变量result，并打印出结果。

打印格式：计算结果为...
*/
#include <stdio.h>

int main() {
    int num_1 = 8;
    char ch = 'e';
    float num_2 = 1.23;
    double num_3 = 4.98;
    double result;

    result = (double)ch + num_1;
    printf("计算结果为%lf\n", result);
    result = (int)(num_2 + num_3);
    printf("计算结果为%lf\n", result);
}