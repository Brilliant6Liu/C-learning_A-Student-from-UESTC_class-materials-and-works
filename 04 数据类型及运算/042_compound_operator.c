/*
题目：
1、定义一个int类型变量num，赋初始值为50。
2、通过复合运算符，依次完成以下操作：
（1）将num增加20。
（2）将num减去10。
（3）将num乘以2。
（4）将num除以5。
（5）将num对7取余。
3、要求打印出每一步的计算结果。

打印格式：num = ...
*/
#include <stdio.h>

int main() {
    int num = 50;

    num += 20;
    printf("num = %d\n", num);
    num -= 10;
    printf("num = %d\n", num);
    num *= 2;
    printf("num = %d\n", num);
    num /= 5;
    printf("num = %d\n", num);
    num %= 7;
    printf("num = %d\n", num);
}