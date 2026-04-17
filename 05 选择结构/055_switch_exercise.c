#include <stdio.h>

int main() {
    /*
    练习1：
    写一段代码，实现两数之间的加减乘除运算。
    1、定义三个double类型变量num_1和num_2，并分别赋初始值为11.2和2。
    2、定义一个char类型变量op来储存运算符，赋初始值为'*'。
    3、定义一个double类型变量result来储存num_1和num_2的计算结果，赋初始值为0。
    4、利用switch语句，根据运算符进行相应的计算，最后打印出计算结果。
    打印要求：
    1）有效运算时，打印出计算结果：num_1 + num_2 = result
    （要求打印出变量的实际数字，且保留2位数字，例：11.20 + 2.00 = 13.20）。
    2）进行除法时，若除数为0，就打印出错误提示“错误：除数不能为0。”。
    3）若运算符不是加减乘除中的任何一个，
    就打印出错误提示“错误：不是有效的运算符，仅支持加、减、乘、除运算。”。
    */
    double num_1 = 11.2;
    double num_2 = 0;
    char op = '%';
    double result = 0;

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

    /*
    练习2：
    定义一个int类型变量num用来储存一个整数（0~999之间的任意整数），并赋初始值为123。
    使用嵌套switch语句，完成以下操作：
    1、当num的百位数是0时，将num乘以它的个位数，并打印出num更新后的值。
    2、当num的百位数是1时，若个位数是偶数，将num除以2；
    若个位数是奇数，则将num乘以它的十位数。最后打印出更新后的num值。
    3、当num的百位数既不是0，也不是1时，打印出“num的百位数不是0或1”。
    */
    int num = -123;
    int hundreds = num / 100;
    int tens = (num % 100) / 10;
    int ones = num % 10;

    if (num < 0) {
        printf("num的值要在0到999之间\n");
        return 1;
    }

    if (num > 999) {
        printf("num的值要在0到999之间\n");
        return 1;
    }

    switch(hundreds) {
        case 0:
            num *= ones;
            printf("%d\n", num);
            break;
        case 1:
            switch(ones % 2) {
                case 0:
                    num /= 2;
                    printf("%d\n", num);
                    break;
                case 1:
                    num *= tens;
                    printf("%d\n", num);
                    break;
            }
            break;
        default:
            printf("num的百位数不是0或1\n");
    }
}

