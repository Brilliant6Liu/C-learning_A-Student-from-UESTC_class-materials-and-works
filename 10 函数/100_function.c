/*
题目：
1、编写一个函数print_greetings（没有返回值），接收一个字符串name作为参数，打印出相应的问候内容。
内容如下：
[人名]，好久不见！
[人名]，今天天气不错哈。
[人名]，你吃饭了吗？
其中，“[人名]”需替换为具体的人名。
2、在main函数中调用print_greetings函数，传入的参数为字符串字面量"张三"。
*/
#include <stdio.h>

void print_greetings(char *name)
{
    printf("%s，好久不见！\n", name);
    printf("%s，今天天气不错哈。\n", name);
    printf("%s，你吃饭了吗？\n", name);
}

int main()
{
    print_greetings("张三");
}