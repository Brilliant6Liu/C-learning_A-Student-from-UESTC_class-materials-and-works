/*
练习：
编写一个程序，实现一个简单的餐厅点餐系统。
该餐厅提供以下菜品：
1. 汉堡--15元/个
2. 炸鸡--12元/份
3. 薯条--10元/份
在程序中，使用int类型变量dishes储存用户选择的菜品编号，quantity储存用户购买的数量，以及price储存订单总价。
使用char类型变量is_take_out储存用户的外带选择。
假设用户选择购买3份炸鸡并且外带，要求最后要打印出用户的点餐详情以及订单总价。
打印效果如下：
欢迎来到餐厅点餐系统！ 
请选择菜品： 
1. 汉堡--15元/个
2. 炸鸡--12元/份
3. 薯条--10元/份 
请输入你想选择的菜品编号（1-3）：
请输入购买数量：
请选择是否外带？(Y/y: 是, N/n: 否)：
----- 订单详情 ----- 
你选择了[菜品名称]，数量：[购买数量]，需支付：[总价]元。
你选择了[外带/堂食]。
*/
#include <stdio.h>

int main() {
    int dishes;
    int quantity;
    int price = 0;
    char is_take_out;

    printf("欢迎来到餐厅点餐系统！\n");
    printf("请选择菜品：\n");
    printf("1. 汉堡--15元/个\n");
    printf("2. 炸鸡--12元/份\n");
    printf("3. 薯条--10元/份\n");

    printf("请输入你想选择的菜品编号（1-3）：");
    scanf("%d", &dishes);
    if (dishes < 1 || dishes > 3) {
        printf("所选的菜品不存在，请重新选择！\n");
        return 1;
    }

    printf("请输入购买数量：");
    scanf("%d", &quantity);
    if (quantity <= 0) {
        printf("购买数量应大于0，请重新输入！\n");
        return 1;
    }

    printf("请选择是否外带？（Y/y：是，N/n：否）：");
    scanf(" %c", &is_take_out);
    if (is_take_out != 'Y' && is_take_out != 'y' && is_take_out != 'N' && is_take_out != 'n') {
        printf("无效的选择，请重新输入！\n");
        return 1;
    }

    printf("\n----- 订单详情 -----\n");

    switch(dishes) {
        case 1:
            price = 15 * quantity;
            printf("你选择了汉堡，数量：%d，需支付：%d元。\n", quantity, price);
            break;
        case 2:
            price = 12 * quantity;
            printf("你选择了炸鸡，数量：%d，需支付：%d元。\n", quantity, price);
            break;
        case 3:
            price = 10 * quantity;
            printf("你选择了薯条，数量：%d，需支付：%d元。\n", quantity, price);
            break;
    }

    switch(is_take_out) {
        case 'Y':
        case 'y':
            printf("你选择了外带。\n");
            break;
        case 'N':
        case 'n':
            printf("你选择了堂食。\n");
            break;
    }
}