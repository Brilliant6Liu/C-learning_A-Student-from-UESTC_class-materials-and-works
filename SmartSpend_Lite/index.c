/*
输入一个字符串，要求按相反的顺序输出各个字符。例如，输入为AbcD，则输出为DcbA。
提示：这个题与习题4.1类似，但需注意的是：
输入输出格式要求：
    输入格式：string回车
    输出格式：gnirts
例如：
输入：hello回车
输出：olleh
*/
#include <stdio.h>
int main()
{
    char a[500];
    int b, sum = 0;
    while (1)
    {
        b = getchar();
        a[sum] = b;
        sum++;
        if (b == '\n')
        {
            break;
        }
    }
    for (int i = sum - 2; i >= 0; i--)
    {
        printf("%c", a[i]);
    }
    return 0;
}