#include <math.h>
#include <stdio.h>

int main() {
    /*
    练习1、编写一个C语言程序，计算一个圆的周长和面积（Π取3.14）。
    要求：
    1、定义3个double类型变量r、c和s，分别储存圆的半径、周长和面积。
    2、计算并打印出半径为8时，圆的周长和面积（保留2位小数）。
    打印格式：
    半径为...时，圆的周长为...
    半径为...时，圆的面积为...
    */
    double r = 8;
    double c;
    double s;

    c = 2 * 3.14 * r;
    s = 3.14 * pow(r, 2);
    printf("半径为%.2lf时，圆的周长为%.2lf\n", r, c);
    printf("半径为%.2lf时，圆的面积为%.2lf\n", r, s);

    /*
    练习2、编写一个C语言程序，用来计算平面直角坐标系中两点 (x1, y1) 和 (x2, y2) 之间的距离。
    要求：
    1、把变量x_1、y_1、x_2和y_2定义为double类型。
    2、定义一个double类型变量dist储存两点之间的距离。
    2、计算并打印出点（2, 8）和点（6, 5）之间的距离（保留2位小数）。

    打印格式：两点之间的距离为...
    */
    double x_1 = 2;
    double y_1 = 8;
    double x_2 = 6;
    double y_2 = 5;
    double dist;

    dist = sqrt(pow(x_1 - x_2, 2) + pow(y_1 - y_2, 2));
    printf("两点之间的距离为%.2lf\n", dist);
}

