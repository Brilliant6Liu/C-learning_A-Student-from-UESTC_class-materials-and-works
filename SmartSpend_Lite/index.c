// 输入一个整数，作为一个整数数组的大小，输入数组，升序排列，奇数在偶数前面（冒泡）。

#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    printf("数组大小:");
    scanf("%d", &n);
    int *arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", *arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d", *arr[i]);
    }

    return 0;
}