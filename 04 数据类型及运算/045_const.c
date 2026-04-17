/*
题目：
1、定义一个常量PI，其值设定为3.14，分别计算出半径为2和8的圆的的面积，并打印出结果，结果保留2位小数。
2、将PI的值调整为3.1415，分别计算出半径为2和8的圆的的面积，并打印出结果，结果保留2位小数。
*/
#include <math.h>
#include <stdio.h>

int main() {
    const float PI = 3.1415;
    float s;
    s = PI * pow(2,2);
    printf("半径为2的圆的面积是：%.2f\n", s);
    s = PI * pow(8,2);
    printf("半径为8的圆的面积是：%.2f\n", s);
}