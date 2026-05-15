/*
题目：
编写一段代码，要求用getchar和putchar函数，实现如下功能：
根据用户输入的字母，进行大小写转换。
当用户输入的是大写字母时，将其转换为对应的小写字母，并用putchar函数输出转换后的结果。
当用户输入的是小写字母时，将其转换为对应的大写字母，并用putchar函数输出转换后的结果。
当用户输入的不是字母时，输出错误提示“错误：输入的不是字母。”。

提示：大写字母的ASCII码值加上32，即为对应小写字母的ASCII码值
*/
// 也可以这么写：
// putchar(a - 'A' + 'a');

#include <stdio.h>

int main()
{
    char ch;

    printf("请输入一个字母：");
    ch = getchar();

    if (ch >= 'A' && ch <= 'Z')
    {
        ch += 32;
    }
    else if (ch >= 'a' && ch <= 'z')
    {
        ch -= 32;
    }
    else
    {
        printf("你输入的不是一个有效的字母。\n");
        return 1;
    }

    putchar(ch);
    putchar('\n');
}