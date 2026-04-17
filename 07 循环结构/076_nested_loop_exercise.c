#include <stdio.h>

int main() {
/*
    练习1：编写一段代码，使用for循环嵌套for循环来打印一个等腰三角形，三角形的行数由用户输入决定。
    定义一个int类型变量rows来储存三角形的行数。
    示例：行数为4的等腰三角形。
       *
      ***
     *****
    *******
*/
    int rows;
    printf("请输入三角形的行数：");
    scanf("%d", &rows);

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= rows - i; j++) {
            printf(" ");
        }
        for (int k = 1; k <= 2 * i - 1; k++) {
            printf("*");
        }
        printf("\n");
    }

/*
    练习2：编写一段代码，使用while循环嵌套while循环打印一个菱形。
    菱形的行数由用户输入决定，且输入的行数必须为奇数。
    定义一个int类型变量rows来储存菱形的行数。
    示例：行数为5的菱形。
      *
     ***
    *****
     ***
      *
*/
    int rows;
    printf("请输入菱形的行数（奇数）：");
    scanf("%d", &rows);

    if (rows % 2 == 0) {
        printf("请输入一个奇数。\n");
        return 1;
    }

    int i = 1;
    while (i <= rows / 2 + 1) {
        int j = 1;
        while (j <= (rows / 2 + 1) - i) {
            printf(" ");
            j++;
        }
        int k = 1;
        while (k <= 2 * i - 1) {
            printf("*");
            k++;
        }
        printf("\n");
        i++;
    }

    i = rows / 2;
    while (i >= 1) {
        int j = 1;
        while (j <= (rows / 2 + 1) - i) {
            printf(" ");
            j++;
        }
        int k = 1;
        while (k <= 2 * i - 1) {
            printf("*");
            k++;
        }
        printf("\n");
        i--;
    }
}

