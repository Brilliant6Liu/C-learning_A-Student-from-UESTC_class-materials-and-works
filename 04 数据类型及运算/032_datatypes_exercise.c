/*
练习：
有两个学生的个人信息如下：
名字 | 班级 | 身高（cm） | 体重（kg） | 性别
Mike |  A  |  187.5    |    68      |  M
Amy  |  B  |   174     |   55.8     |  F

请把除了姓名外的其他个人信息都定义成变量，再通过这些变量打印出他们的个人信息。
打印格式例子如下：Mike {Class A, 187.50cm, 68.00kg, M}，要求身高体重保留两位小数。
*/
#include <stdio.h>

int main() {
    char mike_class = 'A';
    float mike_height = 187.5;
    float mike_weight = 68;
    char mike_sex = 'M';
    char amy_class = 'B';
    float amy_height = 174;
    float amy_weight = 55.8;
    char amy_sex = 'F';

    printf("Mike {Class %c, %.2fcm, %.2fkg, %c}\n", mike_class, mike_height, mike_weight, mike_sex);
    printf("Amy {Class %c, %.2fcm, %.2fkg, %c}\n", amy_class, amy_height, amy_weight, amy_sex);
}