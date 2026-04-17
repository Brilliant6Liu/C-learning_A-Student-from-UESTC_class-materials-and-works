/*
题目：
1、定义两个长度为50的字符数组str_1和str_2，用来储存用户输入的两个字符串。
2、定义两个int类型变量result和len，并给它们都赋初始值为0。其中，result用来储存两个字符串的比较结果值，len用来储存字符串的长度。
3、将str_2复制到str_1中并输出str_1。
打印格式：复制后的str_1：...
4、将字符串", world"连接到str_1后面并输出str_1。
打印格式：连接后的str_1：...
5、比较字符串str_2与字符串"hello"是否相等并输出结果。
打印格式：如果相等，就打印出“两个字符串相等”；如果不相等，就打印出“两个字符串不相等”。
6、计算字符串str_2的长度并输出。
打印格式：str_2的长度为：...
*/
#include <stdio.h>
#include <string.h>

int main() {
    char str_1[50];
    char str_2[50];
    int result = 0;
    int len = 0;

    printf("请输入第一个字符串：");
    scanf("%s", str_1);
    printf("请输入第二个字符串：");
    scanf("%s", str_2);

    strcpy(str_1, str_2);
    printf("复制后的str_1：%s\n", str_1);

    strcat(str_1, ", world");
    printf("连接后的str_1：%s\n", str_1);

    result = strcmp(str_2, "hello");
    if (result == 0) {
        puts("两个字符串相等");
    }
    else {
        puts("两个字符串不相等");
    }

    len = strlen(str_2);
    printf("str_2的长度为：%d\n", len);
}