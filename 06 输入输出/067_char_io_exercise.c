#include <stdio.h>

int main() {
    /*练习1：
    写一段代码，要求根据用户输入一个大写字母（A-Z），打印出该字母前三位和后三位的字母。
    具体要求：
    1、定义三个char类型变量，ch、prev和next。
    ch用来储存用户输入的字符，prev用来储存该字母前三位的字母，next用来存储该字母后三位的字母，
    并给prev和next赋初始值为字符'?'。
    2、若用户输入的字母不是大写字母，则提示用户输入错误。
    若用户输入的大写字母的前三位或后三位不是大写字母，则用字符'?'表示。
    打印格式：
    在它前三位的字母是...
    在它后三位的字母是...（要求字母使用putchar输出）。
    */
    char ch;
    char prev = '?';
    char next = '?';

    printf("请输入一个大写字母（A-Z）：");
    ch = getchar();

    if (ch >= 'A' && ch <= 'Z') {
        if (ch - 3 >= 'A') {
            prev = ch - 3;
        }
        if (ch + 3 <= 'Z') {
            next = ch + 3;
        }
        printf("在它前三位的字母是");
        putchar(prev);
        putchar('\n');
        printf("在它后三位的字母是");
        putchar(next);
        putchar('\n');
    }
    else {
        printf("输入错误，请输入大写字母（A-Z）！\n");
    }

    /*练习2：
    写一段代码，实现根据用户输入的两个数和运算符（+、-、*、/），进行相应的运算并输出结果。
    1、定义三个double类型变量num_1和num_2。
    2、定义一个char类型变量op来储存运算符。
    3、定义一个double类型变量result来储存num_1和num_2的计算结果，赋初始值为0。
    4、利用switch语句，根据运算符进行相应的计算，最后打印出计算结果。
    打印要求：
    1）有效运算时，打印出计算结果：num_1 + num_2 = result（要求打印出变量的实际数字，且保留2位数字，
    例：11.20 + 2.00 = 13.20）。
    2）进行除法时，若除数为0，就打印出错误提示“错误：除数不能为0。”。
    3）若运算符不是加减乘除中的任何一个，就打印出错误提示“错误：不是有效的运算符，仅支持加、减、乘、除运算。”。
    */
    double num_1;
    double num_2;
    char op;
    double result = 0;

    printf("请输入第一个数：");
    scanf("%lf", &num_1);
    printf("请输入第二个数：");
    scanf("%lf", &num_2);
    getchar();
    printf("请输入运算符（+、-、*、/）：");
    op = getchar();

    switch(op) {
        case '+':
            result = num_1 + num_2;
            break;
        case '-':
            result = num_1 - num_2;
            break;
        case '*':
            result = num_1 * num_2;
            break;
        case '/':
            if (num_2 == 0) {
                printf("错误：除数不能为0。\n");
                return 1;
            }
            else {
                result = num_1 / num_2;
            }
            break;
        default:
            printf("错误：不是有效的运算符，仅支持加、减、乘、除运算。\n");
            return 1;
    }
    printf("%.2lf %c %.2lf = %.2lf\n", num_1, op, num_2, result);
}

