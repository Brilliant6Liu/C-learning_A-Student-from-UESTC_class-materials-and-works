/*
题目：编写一段代码，实现对一个整数加上10的计算，并打印出计算结果。
1、设计一个函数pass_by_value(没有返回值)，使用值传递方式接收一个整数作为参数，
计算该整数加上10的结果，并打印出计算后形参的值。
打印格式：调用了函数，pass_by_value里num的值为：...

2、设计一个函数pass_by_pointer(没有返回值)，使用指针传递方式接收一个地址作为参数，
计算该地址上的整数加上10的结果，并打印出计算后指针所指向变量的值（即形参指向的值）。
打印格式：调用了函数，ptr指向的值为：...

3、在main函数中：
1）定义一个int类型变量num，赋初始值为10。
2）调用pass_by_value函数，并打印出调用前后num的值。
3）调用pass_by_value函数，并打印出调用前后num的值。
打印格式：
值传递(或指针传递)：
调用前，main里num的值为：...
调用后，main里num的值为：...
*/
#include <stdio.h>
void pass_by_value(int a);
void pass_by_pointer(int *b);

int main()
{
}

void pass_by_value(int a)
{
    printf("%d", a + 10);
}