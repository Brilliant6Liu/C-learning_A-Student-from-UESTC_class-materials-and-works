#include <stdio.h>
#include <string.h>
int main()
{
    char word[21];
    scanf("%20s", word);
    int len = strlen(word);

    // 检查长度是否为0
    if (len == 0)
    {
        printf("error");
        return 0;
    }

    // 检查是否全是字母
    for (int i = 0; i < len; i++)
    {
        if (!((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z')))
        {
            printf("error");
            return 0;
        }
    }

    // 将每个字母替换为后面第4个字母
    for (int i = 0; i < len; i++)
    {
        if (word[i] >= 'A' && word[i] <= 'Z')
        {
            word[i] = 'A' + (word[i] - 'A' + 4) % 26;
        }
        else
        {
            word[i] = 'a' + (word[i] - 'a' + 4) % 26;
        }
    }

    printf("%s", word);
    return 0;
}