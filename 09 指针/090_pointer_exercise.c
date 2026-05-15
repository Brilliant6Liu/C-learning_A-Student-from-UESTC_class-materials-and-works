/*
练习：
1、定义两个int类型变量num_1和num_2，并分别赋初始值为5和10。
2、定义两个指针变量ptr_1和ptr_2，ptr_1指向变量num_1，ptr_2指向变量num_2。
3、通过指针来交换这两个变量的值。
要求打印出num_1和num_2交换前后的值。

打印格式：
交换前：num_1是...，num_2是...
*/
#include <stdio.h>

int main()
{
    int num_1 = 5;
    int num_2 = 10;
    int *ptr_1 = &num_1;
    int *ptr_2 = &num_2;

    printf("交换前：num_1是%d，num_2是%d\n", num_1, num_2);
    int temp = *ptr_1;
    *ptr_1 = *ptr_2;
    *ptr_2 = temp;
    printf("交换后：num_1是%d，num_2是%d\n", num_1, num_2);
}