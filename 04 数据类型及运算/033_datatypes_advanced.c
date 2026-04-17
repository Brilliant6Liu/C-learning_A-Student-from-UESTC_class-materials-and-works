/*
题目：
1、定义一个整型变量int_1，和一个无符号整型变量int_2，和一个长整型变量long_1，
都赋值为2147483647，并且打印输出它们的值。
2、在定义语句中，修改变量int_1、int_2和long_1的值为2147483648，再次运行。
3、定义一个短整型变量short_1和一个无符号短整型变量short_2，都赋值为32767，并且打印输出它们的值。
4、在定义语句中，修改变量short_1和short_2的值为32768，再次运行。

打印格式：
变量名: 值
*/
#include <stdio.h>

int main() {
    int int_1 = 2147483648;
    unsigned int int_2 = 2147483648;
    long long_1 = 2147483648;

    printf("int_1: %d\n", int_1);
    printf("int_2: %u\n", int_2);
    printf("long_1: %ld\n", long_1);
    
    short short_1 = 32768;
    unsigned short short_2 = 32768;
    
    printf("short_1: %hd\n", short_1);
    printf("short_2: %hu\n", short_2);
}