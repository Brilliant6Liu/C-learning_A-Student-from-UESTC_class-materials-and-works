#include <stdio.h>

int main() {
    /*
    练习1：
    1、定义一个double类型变量num_f，并赋值为70.99。
    2、定义一个int类型变量num_i和一个char类型变量ch。
    3、将变量num_f强制转换为int类型，并赋值给变量num_i。
    4、将变量num_i赋值给变量ch。
    5、打印出num_i储存的值和ch储存的字符。
    打印格式：ASCII码值...对应的字符是...
    */
    double num_f = 70.99;
    int num_i;
    char ch;

    num_i = (int)num_f;
    ch = num_i;
    printf("ASCII码值%d对应的字符是%c\n", num_i, ch);
    /*
    练习2：
    1、定义两个float类型变量f_1和f_2，分别赋值为1和3。
    2、定义一个double类型变量result，用于储存计算结果。
    3、计算f_1 / f_2，赋值给result，打印出result的值。
    4、计算f_1 / f_2，并且要求将f_1强制转换为double类型，将结果赋值给result，打印出result的值。

    打印格式：
    第3小题：先计算，再将结果自动转换为double类型：...（保留10位小数）
    第4小题：将f_1强制转换为double类型，再计算：...（保留10位小数）
    */
    float f_1 = 1;
    float f_2 = 3;
    double result;

    result = f_1 / f_2;
    printf("先计算，再将结果自动转换为double类型：%.10lf\n", result);
    result = (double)f_1 / f_2;
    printf("将f_1强制转换为double类型，再计算：%.10lf\n", result);
}




