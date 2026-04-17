/*
练习：
1、定义一个结构体，使用typedef为该结构体定义别名为 Student。
此结构体包含学生的相关信息：包含学生姓名name（字符数组，长度为20）、年龄age（int 类型）
和成绩score（别名为Score的结构体，包含语文成绩chinese、数学成绩math和英语成绩english，平均成绩average，
均为double类型）。

2、编写一个函数calculate_average（没有返回值），该函数接收一个Student结构体数组students和数组大小size
作为参数。其功能是计算stuents数组里每个学生的平均成绩，并将平均成绩储存在Score结构体的average成员中。

3、在main中：
1）定义一个包含3个学生信息的Student结构体数组students。
3个学生的具体信息如下：
①姓名：张三，年龄：18，语文成绩：90.0，数学成绩：85.0，英语成绩：92.0。
②姓名：李四，年龄：19，语文成绩：88.0，数学成绩：90.0，英语成绩：86.0。
③姓名：王五，年龄：20，语文成绩：95.0，数学成绩：93.0，英语成绩：90.0。
2）调用calculate_average函数，计算students数组里每个学生的平均成绩，并存储在相应的average成员中。
3）打印出每个学生的姓名、年龄和平均成绩。

打印格式：姓名：...，年龄：...，平均成绩：...（平均成绩保留2位小数）
*/
#include <stdio.h>

typedef struct {
    double chinese;
    double math;
    double english;
    double average;
} Score;

typedef struct {
    char name[20];
    int age;
    Score score;
} Student;

void calculate_average(Student students[], int size) {
    for (int i = 0; i < size; i++) {
        students[i].score.average = (students[i].score.chinese + students[i].score.math + students[i].score.english) / 3;
    }
}

int main() {
    Student students[3] = {
        {"张三", 18, {90.0, 85.0, 92.0}},
        {"李四", 19, {88.0, 90.0, 86.0}},
        {"王五", 20, {95.0, 93.0, 90.0}}
    };

    calculate_average(students, 3);
    for (int i = 0; i < 3; i++) {
        printf("姓名：%s，年龄：%d，平均成绩：%.2lf\n", students[i].name, students[i].age, students[i].score.average);
    }
}
