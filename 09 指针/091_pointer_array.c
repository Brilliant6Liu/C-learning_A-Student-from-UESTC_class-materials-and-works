/*
题目：
1、定义三个double类型变量num_1，num_2和num_3，分别用来储存用户输入的三个浮点数。
2、定义一个double类型变量sum，用来储存变量num_1，num_2，num_3的和，赋初始值为0。
3、定义一个double类型变量average，用来储存变量num_1，num_2，num_3这三个数的平均值。
4、依次读取用户输入的三个浮点数，并分别存到变量num_1，num_2和num_3里。
5、定义一个长度为3的指针数组ptr_arr，用来储存指向num_1、num_2、num_3的指针，
遍历数组并计算出这三个浮点数的和。
5、计算出这三个浮点数的平均值，并打印出计算结果（保留两位小数）。

打印格式：平均值为：...
*/
#include <stdio.h>

int main()
{
    double num_1;
    double num_2;
    double num_3;
    double sum = 0;
    double average = 0;

    printf("请输入第一个浮点数：\n");
    scanf("%lf", &num_1);
    printf("请输入第二个浮点数：\n");
    scanf("%lf", &num_2);
    printf("请输入第三个浮点数：\n");
    scanf("%lf", &num_3);

    double *ptr_arr[3] = {&num_1, &num_2, &num_3};
    for (int i = 0; i < 3; i++)
    {
        sum += *ptr_arr[i];
    }
    average = sum / 3;
    printf("平均值为：%.2lf\n", average);
}