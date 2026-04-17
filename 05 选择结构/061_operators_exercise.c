/*
练习：
给定一个日期2088年2月29日，判断该日期是否合法。
如果合法，计算该日期的下一天日期并输出，格式:下一天日期为...年...月...日。
如果不合法，输出 “错误：提供的日期不合法”。
*/
#include <stdio.h>

int main() {
    int year = 2088;
    int month = 12;
    int day = 31;
    int days_in_month = 0;

    if (year == 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        printf("错误：提供的日期不合法。\n");
        return 1;
    }
    
    int is_leap_year = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 1 : 0;

    switch(month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days_in_month = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days_in_month = 30;
            break;
        case 2:
            days_in_month = is_leap_year ? 29 : 28;
            break;
    }

    if (day <= days_in_month) {
        day++;
        if (day > days_in_month) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        printf("下一天日期为%d年%d月%d日。\n", year, month, day);
    }
    else {
        printf("错误：提供的日期不合法。\n");
        return 1;
    }
}