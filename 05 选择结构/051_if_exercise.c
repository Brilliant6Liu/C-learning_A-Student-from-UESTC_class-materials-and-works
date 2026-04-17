#include <stdio.h>

int main() {
    /*
    练习1：定义一个double类型变量temperature表示温度，并赋初始值为30。
    使用if-else if-else语句，根据温度打印出相应的温度描述。
    温度对应的描述如下：
    温度高于30，为炎热。
    温度高于15且低于或等于30，为舒适。
    温度低于等于15，为寒冷。
    */
    double temperature = 30;

    if (temperature > 30) {
        printf("炎热\n");
    }
    else if (temperature > 15) {
        printf("舒适\n");
    }
    else {
        printf("寒冷\n");
    }

    /*
    练习2：
    用嵌套if语句编写一段代码。
    定义int类型的变量num_1、num_2、num_3和max。
    从给定的三个数 8、-2 、87 中找出最大值，并将其存储在变量max中，最后打印出最大值。
    打印格式：最大值为：...
    */
    int num_1 = 8;
    int num_2 = -2;
    int num_3 = 87;
    int max;

    if (num_1 >= num_2) {
        if (num_1 >= num_3) {
            max = num_1;
        }
        else {
            max = num_3;
        }
    }
    else {
        if (num_2 >= num_3) {
            max = num_2;
        }
        else {
            max = num_3;
        }
    }

    printf("最大值为：%d\n", max);
}

