/*
题目：
1、声明一个int整型变量int_1赋值为80，打印int_1。
2、声明一个char字符型变量char_1赋值为A，只用一个printf语句打印出char_1的字符和对应的ASCII码值。
3、声明一个char字符型变量char_2，将int_1赋值给char_2，打印出char_2的字符。
题目1-题目3的打印格式：变量名：值，例如，int_1：80。
4、打印char字符型在内存中所占用的字节数。
*/

#include <stdio.h>

int main() {
    int int_1 = 80;
    printf("int_1: %d\n", int_1);
    char char_1 = 'A';
    printf("char_1: %c,%d\n", char_1, char_1);
    char char_2 = int_1;
    printf("char_2: %c\n", char_2);
    printf("%zu", sizeof(char));
}