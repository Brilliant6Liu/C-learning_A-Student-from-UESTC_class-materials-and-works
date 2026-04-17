/*
题目：
假设有一个文本文件student_info.txt，其内容如下：
张三 19 88.0
李四 20 95.5
王五 21 71.5

编写代码，使用fscanf函数，从文件student_info.txt中，读取各学生的姓名，年龄和成绩，
并把读取结果分别打印出来。

打印格式如下：
学生姓名：...，年龄：...，成绩：...（其中，成绩保留2位小数）
*/
#include <stdio.h>

int main() {
    char name[20];
    int age;
    float score;
    int result;

    FILE* fp = fopen("student_info.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    while (1) {
        result = fscanf(fp, "%s %d %f", name, &age, &score);
        if (result == 3) {
            printf("学生姓名：%s，年龄：%d，成绩：%.2f\n", name, age, score);
        }
        else if (result == EOF) {
            if (feof(fp)) {
                printf("到达文件末尾\n");
            }
            else if (ferror(fp)) {
                printf("读取文件时发生错误\n");
            }
            break;
        }
        else {
            printf("匹配失败：成功读取%d个参数，跳过当前行\n", result);
            char temp[1024];
            fgets(temp, sizeof(temp), fp);
        }
    }

    fclose(fp);
}
