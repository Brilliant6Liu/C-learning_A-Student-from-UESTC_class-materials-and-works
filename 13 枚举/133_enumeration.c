/*
题目：编写一个程序，将用户输入的整数转换为对应的枚举常量，并打印出对应的星期几。
1、使用typedef关键字定义一个枚举类型Day，包含MON、TUE、WED、THU、FRI、SAT、SUN七个枚举常量，
它们代表的整数值依次为1到7之间的整数，即MON代表1，TUE代表2，以此类推，SUN代表7。
2、在main函数中：
1）定义一个int类型变量input，用于储存用户输入的整数。
2）读取用户输入的整数，并储存到变量input中。
3）定义一个Day类型变量day，并将变量input的值通过强制转换赋值给day。
4）根据day的值，执行不同的操作：
当day的值为MON时，打印“星期一”。
当day的值为TUE时，打印“星期二”。
当day的值为WED时，打印“星期三”。
当day的值为THU时，打印“星期四”。
当day的值为FRI时，打印“星期五”。
当day的值为SAT时，打印“星期六”。
当day的值为SUN时，打印“星期日”。
如果day的值不在1到7这个范围内，则打印 “输入无效”。
*/
#include <stdio.h>

typedef enum Day {
    MON = 1,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
} Day;

int main() {
    int input;

    printf("请输入一个1到7之间的整数：");
    scanf("%d", &input);
    Day day = (Day)input;

    switch(day) {
        case MON:
            printf("星期一\n");
            break;
        case TUE:
            printf("星期二\n");
            break;
        case WED:
            printf("星期三\n");
            break;
        case THU:
            printf("星期四\n");
            break;
        case FRI:
            printf("星期五\n");
            break;
        case SAT:
            printf("星期六\n");
            break;
        case SUN:
            printf("星期日\n");
            break;
        default:
            printf("输入无效\n");
    }
}