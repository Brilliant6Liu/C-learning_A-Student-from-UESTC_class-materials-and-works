/*
题目：
1、定义一个结构体，其标签为Student，同时使用typedef为该结构体定义别名为Student。
此结构体包含学生的相关信息：姓名name（字符数组，长度为20）、年龄age（int类型）和成绩score（double类型）。
2、编写一个函数input_student_info（没有返回值），该函数接收一个指向Student结构体变量的指针stu作为参数，
用于读取用户输入学生的信息，并储存到指针stu指向的变量中。
3、在main函数中：
1）定义一个Student结构体变量stu。
2）调用input_student_info函数，读取用户输入的学生信息，并储存到变量stu里。
3）直接操作变量stu来访问成员值，并打印出学生的信息。

打印格式：
学生姓名：...，学生年龄：...，学生成绩：...（成绩保留2位小数）
*/
#include <stdio.h>

typedef struct Student {
    char name[20];
    int age;
    double score;
} Student;

void input_student_info(Student* stu) {
    printf("请输入学生姓名：");
    scanf("%s", stu->name);
    printf("请输入学生年龄：");
    scanf("%d", &stu->age);
    printf("请输入学生成绩：");
    scanf("%lf", &stu->score);
}

int main() {
    Student stu;
    input_student_info(&stu);
    printf("学生姓名：%s，学生年龄：%d，学生成绩：%.2lf\n", stu.name, stu.age, stu.score);
}