#include <stdio.h>

int main() {
    /*
    练习1：
    1、定义一个整型变量a和一个整型变量b，分别初始化为5和3，并且分别打印出a和b进行按位与、按位或、按位异或的结果。
    2、分别给变量a和b重新赋值为-8和12，也别它们进行按位与、按位或、按位异或的结果打印出来。
    打印格式：
    按位与的结果为...
    按位或的结果为...
    按位异或的结果为...
    */
    int a = 5;
    int b = 3;
    printf("按位与的结果为%d\n", a & b);
    printf("按位或的结果为%d\n", a | b);
    printf("按位异或的结果为%d\n", a ^ b);
    a = -8;
    b = 12;
    printf("\n按位与的结果为%d\n", a & b);
    printf("按位或的结果为%d\n", a | b);
    printf("按位异或的结果为%d\n", a ^ b);
    
    /*
    练习2：
    已知某品牌的手机库存还有120部，电视库存还有188部，可在登记库存时，把这两个数据登反了，现在要把两个库存数纠正过来，并且把纠正前后的库存数量都打印出来。

    打印格式：
    修改前/后：
    手机库存为...
    电视库存为...
    */
    int phone_stock = 188;
    int tv_stock = 120;
    printf("修改前：\n");
    printf("手机库存为%d\n", phone_stock);
    printf("电视库存为%d\n", tv_stock);
    int temp = phone_stock;
    phone_stock = tv_stock;
    tv_stock = temp;
    printf("修改后：\n");
    printf("手机库存为%d\n", phone_stock);
    printf("电视库存为%d\n", tv_stock);
}