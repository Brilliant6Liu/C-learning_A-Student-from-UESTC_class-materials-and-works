/*
题目：
定义一个包含5个整数的数组arr，然后用scanf函数从用户获取5个整数，并按顺序储存到数组中。
最后，用for循环分别打印出数组中每个元素的值。
*/
#include <stdio.h>

int main() {
    int arr[5];

    printf("请分5次逐一输入5个整数：\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }
    printf("输入完毕！\n");
    for (int i = 0; i < 5; i++) {
        printf("%d\n", arr[i]);
    }
}