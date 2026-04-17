/*
题目：
给定两个整数a = 2和b = 8。结合if-else语句写出以下代码：
计算出a与b的差值。如果a大于b，打印出a减b的值，否则，打印出b减a的值。
打印格式：a与b的差值为：值
*/
#include <stdio.h>

int main() {
    int a = 2;
    int b = 8;
    int result;

    if (a > b) {
        result = a - b;
    }
    else {
        result = b - a;
    }
    printf("a与b的差值为：%d", result);
}