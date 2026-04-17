/*
题目：编写一段程序，实现计算并打印出用户输入的两个非负整数的阶乘之和。
1、编写一个函数factorial，接收一个整数num作为参数，计算并返回num的阶乘。
n的阶乘：n! = 1 * 2 * ... * n，且规定0的阶乘为1。
2、编写一个函数sum_factorials，接收两个整数a和b作为参数，调用factorial函数，计算并返回a和b的阶乘之和。
3、在main函数中：
1）定义两个int类型变量num_1和num_2，用于储存用户输入的两个整数。
2）获取用户输入的两个非负整数（以空格分隔），并将其分别储存到变量num_1和num_2中。
3）定义一个int类型变量sum，用于储存函数sum_factorials的返回值。调用sum_factorials，
计算并打印出num_1和num_2的阶乘之和，并将其返回值赋给sum。
打印格式：
[第一个整数]! + [第二个整数]! = [两数阶乘之和的结果]，
其中 “[第一个整数]” 和 “[第二个整数]” 需替换为具体的整数值。例：5! + 3! = 126。
*/
#include <stdio.h>

int factorial(int num) {
    int result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

int sum_factorials(int a, int b) {
    int sum = factorial(a) + factorial(b);
    return sum;
}

int main() {
    int num_1;
    int num_2;

    printf("请输入两个非负整数（以空格分隔）：");
    scanf("%d %d", &num_1, &num_2);

    int sum = sum_factorials(num_1, num_2);
    printf("%d! + %d! = %d\n", num_1, num_2, sum);
}