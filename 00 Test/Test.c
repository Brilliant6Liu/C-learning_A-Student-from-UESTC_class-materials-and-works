#include <stdio.h>
#include <math.h>
int main()
{
    int m, n;
    printf("请输入整数: ");
    scanf("%d %d", &m, &n);
    int start = (m < n) ? m : n;
    int end = (m > n) ? m : n;

    for (int i = start; i <= end; i++)
    {
        if (i <= 1)
        {
            continue;
        }
        int bool1 = 1;
        for (int j = 2; j <= sqrt(i) + 1; j++)
        {
            if (i % j == 0)
            {
                bool1 = 0;
                break;
            }
        }

        if (bool1 == 1)
        {
            printf("素数%d\n", i);
        }
    }
    return 0;
}