#include <stdio.h>

int main() {
    /*
    练习1：
    使用for循环实现，让用户输入五个整数（整数以空格分隔，可以包含负数），计算所有正数的和，忽略负数。
    要求定义两个int类型变量num和sum，并给sum赋初始值为0。
    其中，num用于存放用户输入的整数，sum用于储存正数的累加和。
    打印格式：所有正数的和是: ...
    */
    int num;
    int sum = 0;

    printf("请输入五个整数（以空格分隔）：\n");

    for (int i = 0; i < 5; i++) {
        scanf("%d", &num);
        if (num < 0) {
            continue;
        }
        sum += num;
    }

    printf("所有正数的和是：%d\n", sum);

    /*
    练习2：
    使用for循环实现，让用户分五次输入五个整数，
    在遇到第一个负数时停止，并输出该负数（格式：遇到的第一个负数是:...）。
    如果用户输入的都是正数，就输出“全是正数”。
    要求定义一个int类型变量num用于存放用户输入的整数。
    */
    int num;

    printf("请分五次输入五个整数（输入负数时，程序会停止）：\n");

    for (int i = 0; i < 5; i++) {
        scanf("%d", &num);

        if (num < 0) {
            printf("遇到的第一个负数是：%d\n", num);
            break;
        }
    }

    if (num >= 0) {
        printf("全是正数\n");
    }
}

