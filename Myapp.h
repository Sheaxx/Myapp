#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//生成运算符的函数
char signal();
//整数加减乘除的函数
char arithmetic_integer(char sign, int r, int tag);
//整数除法的函数（判断分数是真分数、假分数、整数、0，并化简打印式子）
char division_integer(int numA, int numB, int tag, char sign);
//分数加减乘除的函数
char arithmetic_fraction(char sign, int r, int tag);
//假分数转化为带分数的函数
void change(int a, int b, int* m, int* r);
//辗转相除法求最大公因数
int max_common(int m, int n);
//辗转相除法求最小公倍数
int min_common(int m, int n);
//获取不为0的随机数
int random(int r);