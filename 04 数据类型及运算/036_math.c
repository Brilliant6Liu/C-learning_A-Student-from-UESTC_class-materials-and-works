/*
题目：
1、声明一个int类型变量result_1储存2+10/8*3，并打印出结果。
2、声明一个double类型变量result_2储存2+10/8.0*3，并打印出结果。
以上题目的打印格式：变量名 = 值。
3、写一个一元二次求根公式计算器
*/

#include <stdio.h>
#include <math.h>

int main()
{
    int result_1 = 2 + 10 / 8 * 3;
    printf("result_1 = %d\n", result_1);

    double result_2 = 2 + 10 / 8.0 * 3;
    printf("result_2 = %lf\n", result_2);

    float a, b, c, x1, x2;
    printf("输入参数:");
    scanf("%f %f %f", &a, &b, &c);
    if (b * b - 4 * a * c >= 0)
    {
        x1 = (-b + sqrt(b * b - 4 * a * c)) / 2 * a;
        x2 = (-b - sqrt(b * b - 4 * a * c)) / 2 * a;
        printf("结果是%f和%f", x1, x2);
    }
    else
    {
        printf("不存在实数根");
    }
    return 0;
}