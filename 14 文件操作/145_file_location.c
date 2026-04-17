/*
题目：
1、通过代码创建一个文本文件new_text.txt，并写入如下文本内容:
Hello, world! This is a test.
2、使用fseek函数将文件指针移动到字符串"This"的起始位置，然后，将从该位置起的剩余文本内容,
读取到一个长度为100的字符数组content里，并将content里储存的内容打印出来。
*/
#include <stdio.h>

int main() {
    char content[100];

    FILE* fp = fopen("new_text.txt", "w+");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    int result = fputs("Hello, world! This is a test.\n", fp);
    if (result == EOF) {
        printf("写入失败\n");
        fclose(fp);
        return 1;
    }

    if (fseek(fp, 14, SEEK_SET) != 0) {
        printf("文件位置指示器的移动出现了问题\n");
        fclose(fp);
        return 1;
    }

    if (fgets(content, sizeof(content), fp) != NULL) {
        printf("%s", content);
    }
    else {
        printf("到达文件末尾或读取发生错误\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);
}