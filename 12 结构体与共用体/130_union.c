/*
题目：
1、定义一个共用体，其标签为MultiType。此共用体包含一个int类型成员num、一个长度为10的字符数组str
和一个float类型成员f。
2、在main函数中：
1）定义一个MultiType类型的共用体变量data。
2）定义一个char类型变量choice，用于储存用户的选择。
3）根据用户输入的选择，执行不同的操作：
字符'0'代表退出程序。
字符'1'代表把用户输入的整数存到成员num里，并打印出来。
字符'2'代表把用户输入的字符串（不超9字符）存到成员str里，并打印出来。
字符'3'代表把用户输入的浮点数存到成员f里，并打印出来（保留2位小数）。
如果用户输入其他字符，则提示“输入了无效的选择，请重新输入。” 。

打印格式：
储存的整数/字符串/浮点数为：...
*/
#include <stdio.h>

union MultiType {
    int num;
    char str[10];
    float f;
};

int main() {
    union MultiType data;
    char choice;

    while (1) {
        printf("请输入想储存的数据类型（1-int，2-str，3-float），输入0结束：");
        scanf(" %c", &choice);
        if (choice < '0' || choice > '3') {
            printf("输入了无效的选择，请重新输入。\n");
            continue;
        }
        if (choice == '0') {
            break;
        }
        switch (choice) {
            case '1':
                printf("请输入想储存的整数：");
                scanf("%d", &data.num);
                printf("储存的整数为：%d\n", data.num);
                break;
            case '2':
                printf("请输入想储存的字符串（不超过9个字符）：");
                scanf("%9s", data.str);
                printf("储存的字符串为：%s\n", data.str);
                break;
            case '3':
                printf("请输入想储存的浮点数：");
                scanf("%f", &data.f);
                printf("储存的浮点数为：%.2f\n", data.f);
                break;
        }
    }
}