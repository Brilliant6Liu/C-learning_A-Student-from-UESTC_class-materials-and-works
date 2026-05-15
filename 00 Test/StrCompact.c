#include <stdio.h>
#include <string.h>

int main()
{
    char names[10][50], ids[10][20], genders[10][10];
    char tName[50], tId[20], tGender[10];
    int i, j;

    for (i = 0; i < 10; i++)
    {
        printf("输入第%d个学生的姓名/学号/性别: ", i + 1);
        scanf("%s %s %s", names[i], ids[i], genders[i]);
    }

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9 - i; j++)
        {
            if (strcmp(names[j], names[j + 1]) > 0)
            {
                strcpy(tName, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], tName); // 姓名

                strcpy(tId, ids[j]);
                strcpy(ids[j], ids[j + 1]);
                strcpy(ids[j + 1], tId); // 学号

                strcpy(tGender, genders[j]);
                strcpy(genders[j], genders[j + 1]);
                strcpy(genders[j + 1], tGender); // 性别
            }
        }
    }
    printf("\n排序后的名单:\n");
    for (i = 0; i < 10; i++)
    {
        printf("%s(%s, %s) \t", names[i], ids[i], genders[i]);
        if (i % 2 == 1)
        {
            printf("\n");
        }
    }
    return 0;
}