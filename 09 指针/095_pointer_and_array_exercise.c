#include <stdio.h>
#include <string.h>

int main()
{
    /*
        练习1：
        1、定义三个长度为100的字符数组str_1，str_2和str_3，分别用来储存用户输入的三个字符串。
        2、定义一个int类型变量len，用来储存字符串长度，赋初始值为0。
        3、依次读取用户输入的三个字符串（不含空格），并分别存到变量str_1，str_2和str_3里。
        4、定义一个长度为3的指针数组ptr_arr，用来储存指向str_1，str_2、str_3的指针，
        遍历数组并打印出每个字符串的长度。

        打印格式： 第...个字符串长度为：...
    */
    char str_1[100];
    char str_2[100];
    char str_3[100];
    int len = 0;

    printf("请输入第1个字符串：\n");
    scanf("%s", str_1);
    printf("请输入第2个字符串：\n");
    scanf("%s", str_2);
    printf("请输入第3个字符串：\n");
    scanf("%s", str_3);

    char *ptr_arr[3] = {str_1, str_2, str_3};
    for (int i = 0; i < 3; i++)
    {
        len = strlen(ptr_arr[i]); // strlen 函数需要接收的是一个“字符串的首地址”（即 char* 指针），而不是“字符本身”（因此不是*ptr_arr[i]）
        printf("第%d个字符串长度为：%d\n", i + 1, len);
    }

    /*
        练习2：
        1、定义一个长度为8的char类型数组arr，并初始化其元素为'a'，'b'，'c'，'d'，'e'，'f'，'g'，'h'。
        2、定义一个指针ptr，让其指向数组arr的首元素。
        3、定义一个指针end，让其指向数组arr的最后一个元素，通过对指针ptr进行算术运算来实现。
        4、通过指针访问数组元素，将数组中的字符逆序存储，并打印出逆序后的数组元素。
    */
    char arr[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char *ptr = arr;
    char *end = ptr + 7;

    while (ptr < end)
    {
        char temp = *ptr;
        *ptr = *end;
        *end = temp;
        ptr++;
        end--;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%c ", arr[i]);
    }
    printf("\n");
}
