/*
练习：编写一段程序，判断用户输入的字符串是否是回文串（即字符序列正读和反读都一样，例：level），
并打印出判断结果。
1、编写一个函数is_palindrome，接收的参数包括字符串str，左索引left，右索引right。
函数的功能是判断一个字符串从左索引到右索引之间是否是回文串，如果是，则返回整数1，如果不是，则返回整数0。
2、在main函数中：
1）定义一个长度为50的字符数组str，用于储存用户输入的字符串。
2）定义一个int类型变量len，用于储存str的字符串长度，并赋初始值为0。
3）读取用户输入的字符串（要求字符个数不超过45），并将其储存到str里。
4）计算str的长度，并将其储存到len里。
5）定义一个int类型变量result，用于储存is_palindrome函数返回的结果；调用is_palindrome函数，
判断str是否是回文串，并将返回值储存到result里。
6）根据result的值，打印出相应的判断结果。

打印格式：
如果是回文串，打印出：...是回文串。
如果不是回文串，打印出：...不是回文串。
*/
#include <stdio.h>
#include <string.h>

int is_palindrome(char str[], int left, int right) {
    if (left >= right) {
        return 1;
    }
    if (str[left] != str[right]) {
        return 0;
    }
    return is_palindrome(str, left + 1, right -1);
}

int main() {
    char str[50];
    int len = 0;

    printf("请输入一个字符串（字符个数不超过45）：");
    scanf("%s", str);
    len = strlen(str);
    int result = is_palindrome(str, 0, len - 1);
    if (result) {
        printf("%s是回文串。\n", str);
    }
    else {
        printf("%s不是回文串。\n", str);
    }
}