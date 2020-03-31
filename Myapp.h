#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//生成运算符的函数
char signal();
//拆分整数数位并存放进e[]
void digit_integer(int num, char e[], int& k);
//在题目数组e[]中拼接运算符
void signstrcat(char sign, char e[], int& k);
//判断符号情况
int order(char s[], int select, int a);
//生成运算数
int numcreate(int t[], int select, int r, char s[]);
//整数除法的函数（判断分数是真分数、假分数、整数、0，并化简打印式子）
char division_integer(int& numA, int& numB, int tag, char e[], int& k, int str[]);
//加减乘除函数
int arithmetic_fraction(int num[], char sign, int r, int& tag, char e[], int& k, int str[]);
//假分数转化为带分数的函数
void change(int a, int b, int* m, int* r);
//辗转相除法求最大公因数
int max_common(int m, int n);
//辗转相除法求最小公倍数
int min_common(int m, int n);
//获取不为0的随机数
int random(int r);
//查找完全重复的题目
int repeat(char e[]);

//分析情况并写入文件
char* classify(int num[], int t[], char s[], int r, int i, FILE* fp1, FILE* fp2);