/*
题目：
分别使用while循环和do while循环遍历1到100（包含100），筛选出计算出所有偶数，
并计算它们的总和，打印出最终的计算结果。
打印格式：1到100中所有偶数的和为：值
*/
#include <stdio.h>

int main() {
    int i = 1;
    int sum_1 = 0;
    int sum_2 = 0;

    while (i <= 100) {
        if (i % 2 == 0) {
            sum_1 = sum_1 + i;
        }
        i = i + 1;
    }

    printf("i = %d\n", i);
    printf("1到100中所有偶数的和为：%d\n", sum_1);

    i = 1;
    do {
        if (i % 2 == 0) {
            sum_2 = sum_2 + i;
        }
        i = i + 1;
    } while (i <= 100);

    printf("1到100中所有偶数的和为：%d\n", sum_2);

}