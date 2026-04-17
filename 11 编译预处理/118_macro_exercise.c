/*
练习1:
1、定义一个宏SQUARE，接收一个参数x，计算出x的平方。
2、在main函数中：
1）定义一个int类型变量num，用于储存用户输入的一个整数。
2）读取用户输入的整数，并将其储存到变量num中。
3）定义一个int类型变量result，将使用宏SQUARE计算出num的平方值的结果赋给变量result，并打印出结果。

打印格式：...的平方是：...
*/
#include <stdio.h>

#define SQUARE(x) ((x) * (x))

int main() {
    int num;

    printf("请输入一个整数：");
    scanf("%d", &num);
    int result = SQUARE(num);
    printf("%d的平方是：%d\n", num, result);
}

/*
练习2：
1、定义一个不带参数的宏SECONDS_PER_MINUTE，值为60，用于表示每分钟的秒数。
2、定义一个带参数的宏MINUTES_TO_SECONDS，接收一个参数m，用于将分钟数m转换为秒数。
3、在main函数中：
1）定义一个int类型变量minutes，用于储存用户输入的分钟数。
2）读取用户输入的一个整数，并将其储存到变量minutes中。
3）定义一个int类型变量seconds，将使用宏MINUTES_TO_SECONDS进行转换的结果赋给变量seconds，并打印出结果。

打印格式：...分钟等于...秒
*/
#include <stdio.h>

#define SECONDS_PER_MINUTE 60
#define MINUTES_TO_SECONDS(m) ((m) * (SECONDS_PER_MINUTE))

int main() {
    int minutes;

    printf("请输入分钟数（要求整数）：");
    scanf("%d", &minutes);
    int seconds = MINUTES_TO_SECONDS(minutes);
    printf("%d分钟等于%d秒\n", minutes, seconds);
}