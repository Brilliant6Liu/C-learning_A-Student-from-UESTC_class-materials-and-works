/*
练习1：编写一个程序，实现将用户输入的字符串倒序输出。
1、编写一个指针函数reverse_string，它接收一个字符串指针str作为参数，
返回一个新的字符串指针reversed（使用malloc分配内存），该指针指向原字符串逆序后的字符串。

2、在main函数中：
1）定义一个长度为50的字符数组str，用于储存用户输入的字符串。
2）读取用户输入的一个字符串（不超过45个字符），并将其储存到str里。
3）定义一个字符串指针reversed_str，用于储存reverse_string函数返回的结果值；
调用reverse_string函数，并将返回值储存到reversed_str里。
4）打印出逆序后的字符串，然后释放使用malloc函数分配的内存。

打印格式：逆序后的字符串是：...
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverse_string(char* str) {
    int len = strlen(str);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        printf("内存分配失败\n");
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

int main() {
    char str[50];

    printf("请输入一个字符串（字符个数不超过45）：");
    scanf("%s", str);
    char* reversed_str = reverse_string(str);
    if (reversed_str != NULL) {
        printf("逆序后的字符串是：%s\n", reversed_str);
        free(reversed_str);
    }
}

/*
练习2：编写一段程序，实现根据用户的选择，调用不同的函数来打印用户输入的两个整数中的较大值或较小值。
1、编写一个函数max，它接收两个整数a和b作为参数，并返回两个整数中的较大值。
2、编写一个函数min，它接收两个整数a和b作为参数，并返回两个整数中的较小值。
3、编写一个函数operate（没有返回值），它接收两个整数a和b，以及一个函数指针fp作为参数，
要求fp所指向的函数能跟max和min函数匹配，在该函数中，通过指针fp调用不同的函数，并打印出结果。
打印格式：结果是:...

4、在main函数中：
1）定义两个int类型变量num_1和num_2，用于储存用户输入的两个整数。
2）定义一个int类型变量choice，用于储存用户输入的选择，其中，1表示调用max函数，2表示调用min函数。
3）读取用户输入的两个整数和选择，并分别储存到变量num_1、num_2和choice里。
4）调用operate函数，注意根据用户的选择，传递不同的函数指针。
*/
#include <stdio.h>

int max(int a, int b) {
    int result = a > b? a : b;
    return result;
}

int min(int a, int b) {
    int result = a < b? a : b;
    return result;
}

void operate(int a, int b, int (*fp)(int, int)) {
    int result = fp(a, b);
    printf("结果是：%d\n", result);
}

int main() {
    int num_1;
    int num_2;
    int choice;

    printf("请输入两个整数（以空格分隔）：");
    scanf("%d %d", &num_1, &num_2);
    printf("请输入选择（1 - 取较大值，2 - 取较小值）：");
    scanf("%d", &choice);

    if (choice == 1) {
        operate(num_1, num_2, max);
    }
    else if (choice == 2) {
        operate(num_1, num_2, min);
    }
    else {
        printf("错误：选择无效！\n");
        return 1;
    }
}