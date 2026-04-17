/*
练习：编写一个程序，允许用户选择计算圆形或矩形的面积，并根据选择输入相应的参数进行计算。
1、定义一个不带参数的宏PI，值为3.14，用于表示圆周率。
2、定义一个共用体，其标签为ShapeData。
此共用体包含一个float类型成员radius，用于储存圆形的半径，以及一个结构体成员rectangle，
该结构体包含两个float类型的成员length和width，用于储存矩形的长和宽。
3、在main函数中：
1）定义一个union ShapeData类型的共用体变量shape。
2）定义一个char类型变量choice，用于储存用户的选择。
3）定义一个float类型变量area，用于储存面积的计算结果，给它赋初始值为0。
4）根据用户输入的选择，执行不同的操作：
字符'1'代表把用户输入的半径存到成员radius里，计算出圆的面积赋值给变量area，并打印出结果。
字符'2'代表把用户输入的长和宽分别存到成员rectangle的length和width里，计算出矩形的面积赋值给变量area，
并打印出结果。
如果用户输入其他字符，则提示“输入了无效的选择，程序已结束。” 。

打印格式：
该圆形/矩形面积为:...（保留两位小数）
*/
#include <stdio.h>

#define PI 3.14

union ShapeData {
    float radius;
    struct {
        float length;
        float width;
    } rectangle;
};

int main() {
    union ShapeData shape;
    char choice;
    float area = 0;

    printf("请选择想计算的内容：1-圆形面积，2-矩形面积：");
    scanf(" %c", &choice);
    if (choice == '1') {
        printf("请输入半径：");
        scanf("%f", &shape.radius);
        area = PI * shape.radius * shape.radius;
        printf("该圆形面积为：%.2f\n", area);
    }
    else if (choice == '2') {
        printf("请输入长和宽（用空格分隔）：");
        scanf("%f %f", &shape.rectangle.length, &shape.rectangle.width);
        area = shape.rectangle.length * shape.rectangle.width;
        printf("该矩形面积为：%.2f\n", area);
    }
    else {
        printf("输入了无效的选择，程序已结束。\n");
    }
}