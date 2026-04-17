/*
练习1：
1、在当前目录下创建一个文本文件info.txt，其内容如下：
This is a sample text.
John Doe
25
93.14
Football

2、编写代码，使用fgetc、fgets从info.txt文件中读取数据。
要求：
1）使用fgets函数读取文件的第一行，并打印出来。
2）使用fgetc函数统计文件中剩余行里的字母总数。
*/
#include <stdio.h>

int main() {
    char line[100];
    int ch;
    int count = 0;

    FILE* fp = fopen("info.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    if (fgets(line, sizeof(line), fp) != NULL) {
        printf("第一行内容：%s\n", line);
    }
    else {
        printf("到达文件末尾或读取发生错误\n");
    }

    ch = fgetc(fp);
    while (ch != EOF) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            count++;
        }
        ch = fgetc(fp);
    }
    printf("除第一行外字母总数：%d\n", count);

    fclose(fp);
}



/*
练习2：
要求编写程序，使用fread函数从名为students.bin的二进制文件中读取多个学生的信息，并将每个学生的姓名、
年龄和成绩出储存到一个Student类型的数组students里，并按格式把数组打印出来。
已知：
1、students.bin文件里储存的学生信息数量为3。
2、别名为Student结构体包含姓名、年龄和成绩三个成员。

打印格式：
姓名：...，年龄：...，成绩：...（成绩保留2位小数） 
*/
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    float score;
} Student;

int main() {
    Student students[3];

    FILE* fp = fopen("students.bin", "rb");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    size_t result = fread(students, sizeof(Student), 3, fp);
    if (result != 3) {
        if (feof(fp)) {
            printf("到达文件末尾\n");
        }
        else if (ferror(fp)) {
            printf("读取文件时发生错误\n");
        }
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        printf("姓名：%s，年龄：%d，成绩：%.2f\n", students[i].name, students[i].age, students[i].score);
    }

    fclose(fp);
}