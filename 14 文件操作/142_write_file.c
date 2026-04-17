/*
题目：
1、使用fputs函数将以下内容写入text.txt文件中。
待写入内容：
我欲乘风归去，
又恐琼楼玉宇，
高处不胜寒。

2、使用fputs函数将以下内容追加到text.txt文件末尾。
待追加内容：
起舞弄清影，
何似在人间。
*/
#include <stdio.h>

int main() {
    FILE* fp = fopen("text.txt", "w");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    char text[] = "我欲乘风归去，\n又恐琼楼玉宇，\n高处不胜寒。\n";
    int result = fputs(text, fp);
    if (result == EOF) {
        printf("写入失败\n");
        fclose(fp);
        return 1;
    }

    if (fclose(fp) != 0) {
        printf("关闭文件失败，数据可能未写入磁盘\n");
        return 1;
    }
    printf("写入成功\n");

    fp = fopen("text.txt", "a");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    char new_text[] = "起舞弄清影，\n何似在人间。\n";
    result = fputs(new_text, fp);
    if (result == EOF) {
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