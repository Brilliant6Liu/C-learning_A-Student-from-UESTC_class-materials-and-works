/*
练习：编写一个程序，根据用户输入的月份数字，确定对应的季节枚举常量，并打印出月份所在的季节。
1、使用typedef关键字定义一个枚举类型Season，包含 SPRING、SUMMER、AUTUMN、WINTER四个枚举常量，
分别代表春、夏、秋、冬四季。
2、编写一个函数get_season，该函数接收一个月份数字month作为参数，功能是根据month的值,
返回相应的Season枚举常量。其中，3-5月是春季，6-8月是夏季，9-11月是秋季，12-2月是冬季。
3、在main函数中：
1）定义一个int类型变量month，用于储存用户输入的月份数字。
2）读取用户输入的月份数字，并储存到变量month中。
3）定义一个Season类型变量season，并把调用get_season函数的返回值赋给season。
4）根据season的值，执行不同的操作：
当season的值为SPRING时，打印 “该月份在春季”。
当season的值为SUMMER时，打印 “该月份在夏季”。
当season的值为AUTUMN时，打印 “该月份在秋季”。
当season的值为WINTER时，打印 “该月份在冬季”。
*/
