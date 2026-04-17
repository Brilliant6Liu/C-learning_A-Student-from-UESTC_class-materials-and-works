/*
练习1：
1、定义一个结构体，其别名为Person。此结构体包含个人的相关信息：姓名name（字符数组，长度为20）、
年龄age（int类型）和身高height（float 类型）。
2、使用fprintf函数将一个Person结构体变量person的信息，按照特定格式写入文件person.txt中。
格式要求如下：
姓名：...，年龄：...，身高：...（其中，身高保留2位小数）
*/
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    float height;
} Person;

int main() {
    Person person = {"Tom", 25, 1.75};

    FILE* fp = fopen("person.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    int result = fprintf(fp, "姓名：%s，年龄：%d，身高：%.2f\n", person.name, person.age, person.height);
    if (result < 0) {
        printf("写入失败\n");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0) {
        printf("关闭文件失败，数据可能未写入磁盘\n");
        return 1;
    }
    printf("写入成功\n");
}

/*
练习2：
1、定义一个结构体，其别名为Person。此结构体包含个人的相关信息：姓名name（字符数组，长度为20）、
年龄age（int类型）和身高height（float 类型）。
2、创建一个Person结构体数组persons，初始化一些个人信息，内容如下：
姓名  年龄  身高
Tom   25   1.75
Alice 20   1.68
Bob   21   1.80
3、使用fwrite函数将persons数组中的学生信息写入person.bin文件，
再使用fread函数读取person.bin文件中的信息，并储存到Person结构体数组read_data里，打印出来。
*/
#include <stdio.h>

typedef struct {
    char name[20];
    int age;
    float height;
} Person;

int main() {
    Person persons[3] = {
        {"Tom", 25, 1.75},
        {"Alice", 20, 1.68},
        {"Bob", 21, 1.80}
    };
    Person read_data[3];

    FILE* fp = fopen("person.bin", "wb");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    size_t result = fwrite(persons, sizeof(Person), 3, fp);
    if (result != 3) {
        printf("写入错误或磁盘空间不足\n");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0) {
        printf("关闭文件失败，数据可能未写入磁盘\n");
        return 1;
    }
    printf("写入成功\n");

    fp = fopen("person.bin", "rb");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    result = fread(read_data, sizeof(Person), 3, fp);
    if (result != 3) {
        printf("到达文件末尾或读取错误\n");
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        printf("姓名：%s，年龄：%d，身高：%.2f\n", read_data[i].name, read_data[i].age, read_data[i].height);
    }

    fclose(fp);
}