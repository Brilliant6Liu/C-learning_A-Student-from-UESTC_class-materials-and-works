#include <stdio.h>
#include <math.h>

int main() {
    /*
    练习1：编写一段代码，根据已知的光速和时间（秒为单位），计算光在指定时间内传播的距离。要求计算光在5秒内传播的距离，并打印出结果。
    要求光速和时间定义为double类型，以确保精度。

    提示：
    1、光速约为299792458米/秒
    2、某段时间内光传播的距离 = 光速 * 时间
    打印格式：光在...秒内传播的距离是...米(保留2位小数)
    */
    const double SPEED_OF_LIGHT = 299792458;
    double seconds = 8;
    double distance = SPEED_OF_LIGHT * seconds;
    printf("光在%.2lf秒内传播的距离是%.2lf米\n", seconds, distance);

    /*
    练习2：编写一段代码，根据已知的下落高度和重力加速度，计算一个物体从指定高度自由下落所需的时间。
    要求计算一个物体从10米高处自由下落所需的时间，并打印出结果。
    要求重力加速度和下落高度定义为double类型，以确保精度。

    提示：
    1、重力加速度约为9.8米/秒²
    2、物体的下落距离 = （重力加速度 * 时间²）÷ 2
    打印格式：物体从...米高处自由下落所需的时间是...秒（保留2位小数）
    */
    const double G = 9.8;
    double height = 20;
    double time = sqrt(height * 2 / G);
    printf("物体从%.2lf米高处自由下落所需的时间是%.2lf秒\n", height, time);

    /*
    练习3：编写一段代码，根据已知的千克数，求出对应的磅数。要求计算并打印出将5千克转换为磅的结果。
    要求千克数和磅数定义为double类型，以确保精度。

    提示：1千克约为2.20462磅
    打印格式：...千克约等于...磅（保留2位小数）
    */
    const double KG_TO_POUND = 2.20462;
    double kg = 10;
    double pounds = kg * KG_TO_POUND;
    printf("%.2lf千克约等于%.2lf磅\n", kg, pounds);
}



