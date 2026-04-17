/*
题目：编写一段程序，实现根据用户的选择，调用不同的函数来打印用户输入的两个整数中的较大值或较小值。
1、编写一个函数max，它接收两个整数a和b作为参数，并返回两个整数中的较大值。
2、编写一个函数min，它接收两个整数a和b作为参数，并返回两个整数中的较小值。
3、在main函数中：
1）定义两个int类型变量num_1和num_2，用于储存用户输入的两个整数。
2）定义一个int类型变量choice，用于储存用户输入的选择，其中，1表示调用max函数，2表示调用min函数。
3）定义一个函数指针fp，用于指向max函数或min函数，赋初始值为NULL。
4）定义一个int类型变量result，用于储存调用函数后返回的结果值，并给它赋初始值为0。
5）读取用户输入的两个整数和选择，并分别储存到变量num_1、num_2和choice里。
6）根据用户的选择，使用函数指针fp调用相应的函数，并将函数返回的结果值储存到result里，要求打印出结果。

打印格式：结果是:...
*/
#include <stdio.h>

int max(int a, int b) {
    int result = a > b? a : b;
    return result;
}

int min(int a, int b) {
    int result = a < b? a : b;
    return result;
}

int main() {
    int num_1;
    int num_2;
    int choice;
    int (*fp)(int, int) = NULL;
    int result = 0;

    printf("请输入两个整数（以空格分隔）：");
    scanf("%d %d", &num_1, &num_2);
    printf("请输入选择（1 - 取较大值，2 - 取较小值）：");
    scanf("%d", &choice);

    if (choice == 1) {
        fp = max;
        result = fp(num_1, num_2);
    }
    else if (choice == 2) {
        fp = min;
        result = fp(num_1, num_2);
    }
    else {
        printf("错误：选择无效！\n");
        return 1;
    }
    printf("结果是：%d\n", result);
}