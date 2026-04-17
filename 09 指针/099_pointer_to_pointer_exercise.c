#include <stdio.h>

int main() {
/*
    练习1：
    1、定义两个长度为20的字符数组str_1和str_2，给str_1赋初始值为字符串"Hello"，
    给str_2赋初始值为"World"。
    2、定义一个指针ptr_1，并让其指向str_1。
    3、定义一个二级指针ptr_2，并让其指向ptr_1。
    4、通过操作二级指针ptr_2（不直接使用ptr_1），使指针ptr_1改为指向str_2。
    要求打印出修改前后ptr_1指向的字符串。
    打印格式：
    修改前，ptr_1指向的字符串是：...
    修改后，ptr_1指向的字符串是：...
*/
    char str_1[20] = "Hello";
    char str_2[20] = "World";
    char* ptr_1 = str_1;
    char** ptr_2 = &ptr_1;

    printf("修改前，ptr_1指向的字符串是：%s\n", ptr_1);
    *ptr_2 = str_2;
    printf("修改后，ptr_1指向的字符串是：%s\n", ptr_1);

/*
    练习2：
    1、定义一个包含5个整数的数组arr，并初始化其元素为1，2，3，4，5。
    2、定义一个指针ptr_1指向数组arr的首元素。
    3、定义一个二级指针ptr_2，并让其指向ptr_1。
    4、仅通过操作二级指针ptr_2（不直接使用ptr_1），对指针ptr_1进行算术运算，遍历并打印数组所有元素。
*/
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr_1 = arr;
    int** ptr_2 = &ptr_1;

    for (int i = 0; i < 5; i++) {
        printf("%d ", *(*ptr_2 + i));
    }
    printf("\n");
}

