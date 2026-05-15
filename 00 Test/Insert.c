/*
将一个整数插入到一个整数数组中合适的位置
（数组元素已经从小到大排序）
（输入得到 整数和数组）
*/

#include <stdio.h>
int main()
{
    printf("输入数组长度:");
    int n;
    scanf("%d", &n);
    int list[n];
    printf("输入数组:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &list[i]);
    }
    
}