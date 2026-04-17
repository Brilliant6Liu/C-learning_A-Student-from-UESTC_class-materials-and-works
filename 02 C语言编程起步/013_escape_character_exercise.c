/*
练习1：
编写一个 C 程序，使用转义字符输出如下图形：
   *
  ***
 *****
*******

练习2：
编写一个C程序，输出以下文本：
This is a "double quoted" text. And here is a backslash\.

练习3：
编写一个C程序，输出以下表格：
Name   Age  City
John   20   New York
Alice  22   London
Bobby  18   Tokyo
*/

#include <stdio.h>

int main() {
    printf("   *\n  ***\n *****\n*******\n");
    printf("========================================================\n");   
    printf("This is a \"double quoted\" text. And here is a backslash\\.\n"); 
    printf("========================================================\n");
    printf("Name\tAge\tCity\n");
    printf("John\t20\tNew York\n");
    printf("Alice\t22\tLondon\n");
    printf("Bobby\t18\tTokyo\n");
    return 0;
}