/*
题目：
1、定义一个结构体，使用typedef为该结构体定义别名为Book。
此结构体包含图书的相关信息：书名title（字符数组，长度为50）、作者author（字符数组，长度为 20）、
价格price（double类型）和库存数量quantity（int类型）。
2、编写一个函数calculate_total_value，该函数接收一个Book结构体数组books和该数组大小size作为参数，
其功能是计算并返回图书的总价值total_value（double类型），计算方式为将数组中每本图书的价格乘以其库存数量，
然后累加求和。
3、在main函数中：
1）定义一个包含3本图书信息的Book结构体数组books。
3本图书的具体信息如下：
①书名：C语言入门教程，作者：谭浩强，价格：30.0，库存：50。
②书名：数据结构，作者：严蔚敏，价格：45.0，库存：30。
③书名：操作系统，作者：汤小丹，价格：55.0，库存：20。
2）定义一个double类型变量total_value，用于储存calculate_total_value函数返回的结果；
调用calculate_total_value函数来计算books数组里所有图书的总价值，并将返回值储存到total_value里。
3）打印出计算出来的总价值。

打印格式：这些图书的总价值为：...（保留2位小数）
*/
#include <stdio.h>

typedef struct {
    char title[50];
    char author[20];
    double price;
    int quantity;
} Book;

double calculate_total_value(Book books[], int size) {
    double total_value = 0;
    for (int i = 0; i < size; i++) {
        total_value += books[i].price * books[i].quantity;
    }
    return total_value;
}

int main() {
    Book books[3] = {
        {"C语言入门教程", "谭浩强", 30.0, 50},
        {"数据结构", "严蔚敏", 45.0, 30},
        {"操作系统", "汤小丹", 55.0, 20}
    };
    double total_value = calculate_total_value(books, 3);
    printf("这些图书的总价值为：%.2lf\n", total_value);
}