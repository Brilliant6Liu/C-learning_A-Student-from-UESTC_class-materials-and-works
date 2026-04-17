/*
题目：已知 Mike 成绩是 98，John 成绩是 89，可在登记成绩时因看错行，导致 Mike 的成绩被错误登记在 John 那里。
现在要把两位的成绩纠正过来。

请完成以下练习：
1、创建两个整型变量mike_score和john_score,分别初始化为89和98。
2、将John的成绩赋值给Mike
3、将John的成绩更改为89
4、打印出两个人的成绩
*/

#include <stdio.h>

int main() {
    int mike_score;
    int john_score;
    mike_score = 89;
    john_score = 98;
    printf("Mike的成绩是%d分。\n", mike_score);
    printf("John的成绩是%d分。\n", john_score);
    mike_score = john_score;
    john_score = 89;
    printf("Mike的成绩是%d分。\n", mike_score);
    printf("John的成绩是%d分。\n", john_score);
}