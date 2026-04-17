#include <stdio.h>
int main()
{
    int a;
    float b, c;
    printf("刘屹洋\n2025082098021\n");
    scanf("%d %f %f", &a, &b, &c);
    if (a >= 0)
    {
        printf("%d\n", a);
    }
    else
    {
        printf("%d\n", -a);
    }
    printf("b+c = %.2f", b + c);
}