/*
练习：
students.bin二进制文件里储存了3条学生信息，并且是使用一个别名为Student的结构体来表示学生信息，
该结构体包含三个成员：名字name（字符数组，长度为20）、年龄age（int类型）和成绩score（float类型）。

现要求完成：
1、读取并打印出students.bin文件所有学生的原始信息。
2、将students.bin文件中第3个学生的名字修改为"Chris"。
2、使用rewind函数，使文件指针回到students.bin文件开头，读取并打印所有Student结构体数据。

打印格式：
修改前/修改后：
名字：...，年龄：...，成绩：...（成绩保留2位小数） 
*/
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    int age;
    float score;
} Student;

int main() {
    Student stu;
    size_t result;

    FILE* fp = fopen("students.bin", "rb+");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    printf("修改前：\n");
    for (int i = 0; i < 3; i++) {
        result = fread(&stu, sizeof(Student), 1, fp);
        if (result != 1) {
            printf("到达文件末尾或读取错误\n");
            fclose(fp);
            return 1;
        }
        printf("名字：%s，年龄：%d，成绩：%.2f\n", stu.name, stu.age, stu.score);
    }

    if (fseek(fp, 2 * sizeof(Student), SEEK_SET) != 0) {
        printf("文件位置指示器的移动出现了问题\n");
        fclose(fp);
        return 1;
    }

    result = fread(&stu, sizeof(Student), 1, fp);
    if (result != 1) {
        printf("到达文件末尾或读取错误\n");
        fclose(fp);
        return 1;
    }

    strcpy(stu.name, "Chris");

    if (fseek(fp, -sizeof(Student), SEEK_CUR) != 0) {
        printf("文件位置指示器的移动出现了问题\n");
        fclose(fp);
        return 1;
    }

    result = fwrite(&stu, sizeof(Student), 1, fp);
    if (result != 1) {
        printf("写入错误或磁盘空间不足\n");
        fclose(fp);
        return 1;
    }

    rewind(fp);

    printf("修改后：\n");
    for (int i = 0; i < 3; i++) {
        result = fread(&stu, sizeof(Student), 1, fp);
        if (result != 1) {
            printf("到达文件末尾或读取错误\n");
            fclose(fp);
            return 1;
        }
        printf("名字：%s，年龄：%d，成绩：%.2f\n", stu.name, stu.age, stu.score);
    }    

    fclose(fp);
}