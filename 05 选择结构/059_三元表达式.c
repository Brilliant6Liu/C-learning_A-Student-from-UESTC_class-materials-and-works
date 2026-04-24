#include <stdio.h>

int main()
{
    /*
    题目1：
    给定两个整数a = 2和b = 8。使用三元表达式，计算并打印出a与b的差值。
    如果a大于b，打印出 a - b 的值；否则，打印出 b - a 的值。
    打印格式：a与b的差值为：...
    */
    int a = 2;
    int b = 8;
    int result = a > b ? a - b : b - a;
    printf("a与b的差值为：%d\n", result);

    /*
    题目2：
    给定一个整数num = 98，使用三元表达式，判断num是否满足大于50，并且能被7整除。
    若满足上述条件，则输出 “满足条件”；否则，输出 “不满足条件”。
    */
    int num = 98;
    (num > 50 && num % 7 == 0) ? printf("满足条件\n") : printf("不满足条件\n");

    // 判断偶数
    int number = 15;
    (number % 2 == 0) ? printf("偶数") : printf("奇数");
}
