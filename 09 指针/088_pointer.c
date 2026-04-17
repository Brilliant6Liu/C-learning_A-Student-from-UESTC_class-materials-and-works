/*
题目：
定义一个char类型变量ch，并初始化为A，
再定义一个指针变量ptr指向变量ch，
然后通过指针修改变量ch的值为a，
要求打印出变量ch修改前后的值。
*/
#include <stdio.h>

int main() {
    char ch = 'A';
    char* ptr = &ch;

    printf("%c\n", *ptr);
    *ptr = 'a';
    printf("%c\n", *ptr);
}