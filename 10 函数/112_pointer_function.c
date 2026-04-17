/*
题目：
1、定义一个指针函数get_array，该函数不需要参数。
1）在函数里定义一个可以存放5个整数的静态局部数组arr，并将其初始化为 {1, 2, 3, 4, 5}。
2）该函数返回的是指向数组arr里首元素的指针。

2、在main函数中：
1）定义一个int类型变量sum，用于储存数组里所有元素的和。
2）定义一个指向int类型的指针ptr，调用指针函数get_array，并将返回值储存到ptr里。
3）通过对指针ptr进行运算，计算数组里所有元素的总，要求打印出来。

打印格式：总和为:...
*/
#include <stdio.h>

int* get_array() {
    static int arr[5] = {1, 2, 3, 4, 5};
    return arr;
}

int main() {
    int sum = 0;
    int* ptr = get_array();

    for (int i = 0; i < 5; i++) {
        sum += *(ptr + i);
    }
    printf("总和为：%d\n", sum);
}