/*
题目：
1、编写一个函数calculate_bmi，接收体重weight（double类型）和身高height（double类型）作为参数，
计算并返回BMI值（double类型）。
计算公式：BMI = 体重 ÷ （身高 * 身高）
其中，体重的单位是kg，身高的单位是m。

2、在main函数中：
1）定义一个double类型变量bmi，调用函数calculate_bmi，传入的两个参数，体重为70kg和身高为1.8m，
并将返回值赋给bmi。
2）根据bmi的值，按要求打印出BMI值（保留两位小数）和相应的BMI分类。
BMI分类如下：
偏瘦：BMI <= 18.5；
正常：18.5 < BMI <= 25；
偏胖：25 < BMI <= 30；
肥胖：BMI > 30。

打印格式：您的BMI值为：...，BMI分类为：...
*/
#include <stdio.h>

double calculate_bmi(double weight, double height) {
    double bmi = weight / (height * height);
    return bmi;
}

int main() {
    double bmi = calculate_bmi(70, 1.8);
    printf("您的BMI值为：%.2lf，BMI分类为：", bmi);
    if (bmi <= 18.5) {
        printf("偏瘦");
    }
    else if (bmi <= 25) {
        printf("正常");
    }
    else if (bmi <= 30) {
        printf("偏胖");
    }
    else {
        printf("肥胖");
    }
    printf("\n");
}