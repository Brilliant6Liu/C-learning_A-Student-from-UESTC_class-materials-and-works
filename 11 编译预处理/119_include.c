/*
题目：
让用户输入一个字符ch，使用isalpha函数判断该字符是否为字母，并打印出判断结果。
提示：isalpha函数是一个用于判断字符是否为字母的标准库函数，接收一个字符作为参数。isalpha函数属于ctype.h头文件。
若传入的参数是字母，该函数返回一个非零值（一般为真）。
若传入的参数不是字母，该函数返回0（代表假）。

打印格式：...是/不是字母。
*/
#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;

    printf("请输入一个字符：");
    ch = getchar();

    if (isalpha(ch)) {
        printf("%c是字母\n", ch);
    }
    else {
        printf("%c不是字母\n", ch);
    }
}