/*
题目：编写一段代码，让用户输入9个整数（用空格分隔），用这九个整数生成一个3x3的二维数组arr，
并打印出该二维数组的所有元素。
*/
#include <stdio.h>

int main()
{
    int arr[3][3];

    printf("请输入9个整数（用空格分隔）：\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &arr[i][j]);
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}
/*
在 C 里，标准输出 stdout 通常是缓冲的：

对终端/控制台，通常是行缓冲
遇到 \n 时会刷新
遇到 scanf 读取输入时，有时也会自动刷新，但不一定可靠
*/