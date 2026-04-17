/*
题目：
1、编写一个递归函数fibonacci，计算斐波那契数列的第n项。
提示：斐波那契数列的第0项为0，第1项为1，从第2项开始，每一项都等于前两项之和。
例：斐波那契数列的前5项为：0 1 1 2 3。
2、在main函数中：
1）定义一个unsigned int类型变量n，用于表示要计算斐波那契数列的第n项，并给其赋初始值为10。
2）定义一个int类型变量result，用于储存用于储存fibonacci函数返回的结果；调用fibonacci函数，
计算出斐波那契数列的第n项，并将返回值储存到result里。
3）打印出结果。

打印格式：斐波那契数列的第...项是:... 
*/
#include <stdio.h>

int fibonacci(unsigned int n) {
    if (n <= 1) {
        return n;
    }
    else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    unsigned int n = 10;
    int result = fibonacci(n);
    printf("斐波那契数列的第%u项是：%d\n", n, result);
}