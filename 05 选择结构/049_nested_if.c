/*
题目：
定义出用户类型变量user_type（1表示普通用户，2表示会员用户），商品价格变量price，以及最终支付金额变量pay。
某折扣规则如下：
如果是普通用户且商品价格大于100，则打95折，否则无折扣。
如果是会员用户且价格大于200，则打9折，否则打97折。
根据上述折扣规则写出对应嵌套条件语句，并打印出会员购买180元商品时，最终需要支付的金额，支付金额保留两位小数。
打印格式：最终支付金额为：...
*/
#include <stdio.h>

int main() {
    int user_type = 2;
    double price = 180;
    double pay;

    if (user_type == 1) {
        if (price > 100) {
            pay = price * 0.95;
        }
        else {
            pay = price;
        }
    }
    else if (user_type == 2) {
        if (price > 200) {
            pay = price * 0.9;
        }
        else {
            pay = price * 0.97;
        }
    }
    else {
        printf("该用户类型无效\n");
    }

    printf("最终支付金额为：%.2lf\n", pay);
}