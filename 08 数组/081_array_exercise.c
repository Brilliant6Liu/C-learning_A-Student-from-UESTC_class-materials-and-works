#include <stdio.h>

int main() {
/*
    练习1：定义一个可以包含5个整数的数组arr，获取用户输入的5个整数（整数以空格分隔），并储存到数组arr中，
    最后打印出arr里的最大值和最小值。
    打印格式：
    最大值：...
    最小值：...
*/
    int arr[5];

    printf("请输入5个整数（用空格分隔）：\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr[i]);
    }

    int max = arr[0];
    int min = arr[0];

    for (int i = 1; i < 5; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    printf("最大值：%d\n", max);
    printf("最小值：%d\n", min);

/*
    练习2：编写一段代码，实现计算生成杨辉三角的前五行，并打印出来。
    要求定义一个5×5的二维整数数组arr来存储杨辉三角的前五行。

    杨辉三角的前五行如下：
    1 
    1 1 
    1 2 1 
    1 3 3 1 
    1 4 6 4 1

    杨辉三角的特点：
    1、每一行的首尾数字都是1。
    2、中间的数字是上一行相邻两个数字之和。例如，第三行的2等于第二行的1+1。
*/
    int arr[5][5];

    for (int i = 0; i < 5; i++) {
        arr[i][0] = 1;
        arr[i][i] = 1;
    }

    for (int i = 2; i < 5; i++) {
        for (int j = 1; j < i; j++) {
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

