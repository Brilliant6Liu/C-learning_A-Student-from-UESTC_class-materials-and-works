/*
1. 定义6个短整型变量line_1，line_2，line_3，line_7，line_8，line_9分别赋值为1，222，33333，77，88，99。
2. 定义2个整型变量line_4，line_5分别赋值为4444444，555555555。
3. 定义1个长整型变量line_6赋值为66666666666。
4. 打印出如下图案。
            1
          222
        33333
      4444444
    555555555
  66666666666
           77
           88
           99
*/
#include <stdio.h>

int main()
{
  short line_1 = 1;
  short line_2 = 222;
  unsigned short line_3 = 33333;
  short line_7 = 77;
  short line_8 = 88;
  short line_9 = 99;
  int line_4 = 4444444;
  int line_5 = 555555555;
  unsigned long long line_6 = 66666666666;

  printf("%11hd\n", line_1);
  printf("%11hd\n", line_2);
  printf("%11hu\n", line_3);
  printf("%11d\n", line_4);
  printf("%11d\n", line_5);
  printf("%11llu\n", line_6);
  printf("%11hd\n", line_7);
  printf("%11hd\n", line_8);
  printf("%11hd\n", line_9);
}