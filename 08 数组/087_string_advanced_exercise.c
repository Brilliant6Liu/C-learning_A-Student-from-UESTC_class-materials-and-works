/*
练习：编写一段代码，实现简单的用户注册功能。整个注册过程通过循环实现，直到注册成功为止。
1、定义三个长度为25的字符数组user_name，password_1和password_2，
分别用来储存用户输入的用户名、密码和确认密码。
2、定义一个int类型变量len，用来储存用户名或密码的长度，赋初始值为0。
3、定义一个int类型变量result，用来储存两个字符串的比较结果值，赋初始值为0。
4、定义一个int类型变量success，用来表示表示注册的状态，赋初始值为0（0-注册失败，1-注册成功）。

关于注册的具体要求：
1、用户输入的用户名长度要在6到15之间，若用户名长度不符合要求，则提示“用户名长度要在6-15之间，请重新注册!”
2、用户输入的密码长度要在8到20之间，若密码长度不符合要求，则提示“密码长度要在8-20之间，请重新注册!”。
3、设置密码后，要求用户再次输入密码进行确认。若两次输入的密码不一致，则提示“两次输入的密码不同，请重新注册！”；
若一致，则提示“恭喜你注册成功！”。
*/
#include <stdio.h>
#include <string.h>

int main() {
    char user_name[25];
    char password_1[25];
    char password_2[25];
    int len = 0;
    int result = 0;
    int success = 0;

    while (success != 1) {
        printf("请设定用户名（6-15个字符）：");
        scanf("%s", user_name);

        len = strlen(user_name);
        if (len < 6 || len > 15) {
            printf("用户名长度要在6-15之间，请重新注册！\n");
            continue;
        }

        printf("请设定密码（8-20个字符）：");
        scanf("%s", password_1);

        len = strlen(password_1);
        if (len < 8 || len > 20) {
            printf("密码长度要在8-20之间，请重新注册！\n");
            continue;
        }

        printf("请再次输入密码：");
        scanf("%s", password_2);

        result = strcmp(password_1, password_2);
        if (result == 0) {
            printf("恭喜你注册成功！\n");
            success = 1;
        }
        else {
            printf("两次输入的密码不同，请重新注册！\n");
            continue;
        }
    }
}