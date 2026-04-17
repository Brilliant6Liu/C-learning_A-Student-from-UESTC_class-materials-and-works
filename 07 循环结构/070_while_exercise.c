#include <stdio.h>

int main() {
    /*
    练习1：使用while循环实现，让用户输入一系列字符，统计其中字母的个数并输出。

    要求用char类型变量ch储存从用户输入的字符，用int类型变量count来统计字母的个数，并给count赋初始值为0。
    打印格式：字母个数为：...
    */
    char ch;
    int count = 0;

    printf("请输入一系列字符：");
    ch = getchar();

    while (ch != '\n') {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            count++;
        }
        ch = getchar();
    }
    printf("字母个数为：%d\n", count);

    /*
    练习2：使用do while循环，实现一个猜数字游戏。
    如果用户猜的数字小于目标数字，提示 “太小了，再试试！”；
    如果用户猜的数字大于目标数字，提示 “太大了，再试试！”。
    当用户猜对时，输出 “恭喜你，猜对了！”。

    要求定义两个int类型变量，target用来储存目标数字，赋初始值为42；guess用来储存用户输入的猜测数字。
    */
    int target = 42;
    int guess;

    printf("猜数字游戏开始啦！\n");

    do {
        printf("请输入一个数字：");
        scanf("%d", &guess);

        if (guess < target) {
            printf("太小了，再试试！\n");
        }
        else if (guess > target) {
            printf("太大了，再试试！\n");
        }
    } while (guess != target);

    printf("恭喜你，猜对了！\n");
}

