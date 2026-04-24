/*
题目：
编写一段代码，根据房型和住宿天数打印出对应的总价。

计价标准如下：
单人房：住1到3天，每天100元。超过3天的部分，每天80元。
双人房：住1到3天，每天180元。超过3天的部分，每天150元。
豪华套房：每天1000元。

要求：
1、给定的3个int类型变量：房型room_type（1 - 单人房，2 - 双人房，3 - 豪华套房），天数days和总价price，
初始值分别为2，5和0。
2、使用嵌套switch实现。
3、打印格式：...(填入单人房/双人房/豪华套房)，住宿...天，价格为...元。
*/
#include <stdio.h>

int main()
{
    int room_type = 2;
    int days = 5;
    int price = 0;

    if (days < 0)
    {
        printf("执行错误，提供的天数为负数。\n");
        return 1;
    }

    switch (room_type)
    {
    case 1:
        switch (days)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            price = 100 * days;
            break;
        default:
            price = 300 + 80 * (days - 3);
        }
        printf("单人房，住宿%d天，价格为%d元。\n", days, price);
        break;
    case 2:
        switch (days)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            price = 180 * days;
            break;
        default:
            price = 180 * 3 + 150 * (days - 3);
        }
        printf("双人房，住宿%d天，价格为%d元.\n", days, price);
        break;
    case 3:
        price = 1000 * days;
        printf("豪华套房，住宿%d天，价格为%d元。\n", days, price);
        break;
    default:
        printf("找不到匹配的房型。\n");
    }
    return 0;
}