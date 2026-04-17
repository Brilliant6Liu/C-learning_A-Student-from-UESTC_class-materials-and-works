/*
题目：编写一段程序，实现根据用户输入的文件路径和打开模式，对文件进行打开与关闭操作。
1、定义一个数组长度为100的char类型数组file，用于储存用户输入的文件路径。
2、定义一个数组长度为5的char类型数组mode，用于储存用户输入的文件打开模式。
3、读取用户输入的内容，并将其分别存到file和mode里。
4、调用相应的函数，打开和关闭用户指定的文件，并分别检查操作是否成功。
*/
#include <stdio.h>

int main() {
    char file[100];
    char mode[5];

    printf("请输入想打开的文件的路径：");
    scanf("%s", file);
    getchar();
    printf("请指定打开模式：");
    scanf("%s", mode);

    FILE* fp = fopen(file, mode);
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    else {
        printf("成功打开文件\n");
    }

    int result = fclose(fp);
    if (result == 0) {
        printf("成功关闭文件\n");
    }
    else {
        printf("无法关闭文件\n");
    }
}