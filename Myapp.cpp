#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Myapp.h"

//生成运算符的函数
char signal() {
    int num = rand() % 100;
    int mod = num % 4;
    switch (mod) {
        case 0:return '+';
        case 1:return '-';
        case 2:return '*';
        case 3:return '#';
    }
}

//整数加减乘除的函数
char arithmetic_integer(char sign, int r) {
    int num1 = rand() % r;
    int num2 = rand() % r;
    int num3 = random(r);  //分数的分母肯定不为0
    //int num1 = 12, num2 = 30;
    //倍数和余数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(num1, num2);
    char str1[50] = { '\0' };
    char str2[50] = { '\0' };

    //srand((unsigned long)time(0));

    if (sign == '+') {
        printf("%d + %d = %d\n", num1, num2, num1 + num2);
        fputs("ccc", fp1);
        return num1 + num2;
    }
    else if (sign == '-') {
        if (num1 < num2) {//减法结果不能是负数
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }
        printf("%d - %d = %d\n", num1, num2, num1 - num2);
        return num1 - num2;
    }
    else if (sign == '*') {
        printf("%d × %d = %d\n", num1, num2, num1 * num2);
        return num1 * num2;
    }
    else if (sign == '#') {
        //判断余数，能整除则直接打印
        if (num1 == 0 || num3 == 1) {
            printf("%d ÷ %d = %d\n", num1, num3, num1);
        }
        else if (num1 % num3 == 0) {
            printf("%d ÷ %d = %d\n", num1, num3, num1 / num3);
            return num1 / num3;
        }
        else if (num1 > num3) {
            //最大公因数为1
            if (max == 1) {
                change(num1, num3, p1, p2);
                printf("%d ÷ %d = %d'%d/%d\n", num1, num3, *p1, *p2, num3);
            }
            else {
                num1 = num1 / max;
                num3 = num3 / max;
                change(num1, num3, p1, p2);
                printf("%d ÷ %d = %d'%d/%d\n", num1, num3, *p1, *p2, num3);
            }
            return 0;
        }
        else if (num1 < num3) {
            //最大公因数为1
            if (max == 1) {
                printf("%d ÷ %d = %d/%d\n", num1, num3, num1, num3);
            }
            else {
                num1 = num1 / max;
                num3 = num3 / max;
                printf("%d ÷ %d = %d/%d\n", num1, num3, num1, num3);
            }
            return 1;
        }
    }
}

//整数除法的函数
char division_integer(int a, int b) {
    //余数和倍数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(a, b);

    //分子为0或分母为1
    if (a == 0 || b == 1) {
        printf(" = %d\n", a);
        return 0;
    }
    //判断余数，能整除则返回除法答案
    else if (a % b == 0) {
        //printf("%d ÷ %d = %d\n", num1, num2, num1 / num2);
        printf(" = %d\n", a / b);
        return a/b;
    }
    //分子大于分母，是假分数，先化简再化为带分数，返回1
    else if (a > b) {
        //最大公因数为1，无需化简
        if (max == 1) {
            change(a, b, p1, p2);
            printf(" = %d'%d/%d\n", *p1, *p2, b);
        }
        else {
            a = a / max;
            b = b / max;
            change(a, b, p1, p2);
            printf(" = %d'%d/%d\n", *p1, *p2, b);
        }
        return 1;
    }
    //分子小于分母，是真分数，只需要化简，返回2
    else if (a < b) {
        //最大公因数为1
        if (max == 1) {
            printf(" = %d/%d\n", a, b);
        }
        else {
            a = a / max;
            b = b / max;
            printf(" = %d/%d\n", a, b);
        }
        return 2;
    }
}

//分数加减乘除的函数
char arithmetic_fraction(char sign, int r) {
    //分数1
    int num1 = rand() % r;
    int num2 = random(r);
    //分数2
    int num3 = rand() % r;
    int num4 = random(r);
    //分数结果
    int num5, num6;
    //倍数和余数
    int multiple1 = 0, remainder1 = 0, multiple2 = 0, remainder2 = 0;
    int* p1 = &multiple1, * p2 = &remainder1, * p3 = &multiple2, * p4 = &remainder2;
    //两个分数的最大公因数
    int m1 = max_common(num1, num2);
    int m2 = max_common(num3, num4);

    if (sign == '-') {
        //对减的情况做判断，减数小于被减数则两者交换
        if (num1 * num4 - num2 * num3 < 0) {
            int t1, t2, t3;
            t1 = num3;
            num3 = num1;
            num1 = t1;
            t2 = num4;
            num4 = num2;
            num2 = t2;
            //交换两个数后m1和m2也要交换
            t3 = m2;
            m2 = m1;
            m1 = t3;
        }
    }
    
    if (sign == '#' && num3 == 0) {
        num3 = random(r);
        m2 = max_common(num3, num4);
    }

    //判断两个分数是真分数、假分数、整数、0
    if (num1 % num2 == 0) {
        printf("%d %c ", num1 / num2, sign);
    }
    else if (num1 == 0 || num2 == 1) {
        printf("%d %c ", num1, sign);
    }
    else if (num1 > num2) {
        if (m1 == 1) {
            change(num1, num2, p1, p2);
            printf("%d'%d/%d %c ", *p1, *p2, num2, sign);
        }
        else {
            num1 = num1 / m1;
            num2 = num2 / m1;
            change(num1, num2, p1, p2);
            printf("%d'%d/%d %c ", *p1, *p2, num2, sign);
        }
    }
    else if (num1 < num2) {
        if (m1 == 1) {
            printf("%d/%d %c ", num1, num2, sign);
        }
        else {
            num1 = num1 / m1;
            num2 = num2 / m1;
            printf("%d/%d %c ", num1, num2, sign);
        }
    }

    if (num3 % num4 == 0) {
        printf("%d", num3 / num4);
    }
    else if (num3 == 0 || num4 == 1) {
        printf("%d", num3);
    }
    else if (num3 > num4) {
        if (m2 == 1) {
            change(num3, num4, p3, p4);
            printf("%d'%d/%d", *p3, *p4, num4);
        }
        else {
            num3 = num3 / m2;
            num4 = num4 / m2;
            change(num3, num4, p3, p4);
            printf("%d'%d/%d", *p3, *p4, num4);
        }
    }
    else if (num3 < num4) {
        if (m2 == 1) {
            printf("%d/%d", num3, num4);
        }
        else {
            num3 = num3 / m2;
            num4 = num4 / m2;
            printf("%d/%d", num3, num4);        
        }
    }

    if (sign == '+') {
        num5 = num1 * num4 + num3 * num2;
        num6 = num2 * num4;
        division_integer(num5, num6);
    }
    else if (sign == '-') {
        num5 = num1 * num4 - num3 * num2;
        num6 = num2 * num4;
        if (num5 == 0)  printf(" = %d\n", 0);
        else division_integer(num5, num6);
    }
    else if (sign == '*') {
        num5 = num1 * num3;
        num6 = num2 * num4;
        if (num5 == 0)  printf(" = %d\n", 0);
        else division_integer(num5, num6);
    }
    else if (sign == '#') {
        num5 = num1 * num4;
        num6 = num2 * num3;
        if (num5 == 0)  printf(" = %d\n", 0);
        else division_integer(num5, num6);
    }

    return 0;
}

//假分数转化为带分数的函数
void change(int a,int b,int* mu,int* re) {
    //倍数，即带分数的整数部分
    *mu = a / b;
    //余数，即带分数的分数部分的分子
    *re = a % b;
    //带分数转化为m'r/b的真分数形式
}

//辗转相除法求最大公因数
int max_common(int m,int n) {
    //m为分子，n为分母, k为余数
    int k;

    while (n != 0)
    {
        k = m % n;
        m = n;
        n = k;
    }
    //返回最大公因数
    return m;
}

//辗转相除法求最小公倍数
int min_common(int m, int n) {
    //返回值为最小公倍数
    int k;
    k = max_common(m, n);
    if (k != 1) 
        return m * n / k;
    else 
        return m * n;
}

//获取不为0的随机数
int random(int r) {
    int num = rand() % r;
    while (num == 0) {
        num = rand() % r;
    }
    return num;
}

int main() {
    FILE* fp1, * fp2;
    errno_t err1, err2;
    int i = 0;
    int n = 0, r = 0;//n控制生成题目数目，r控制题目中数值范围
    char sign = '+';
    err1 = fopen_s(&fp1, "Exercises.txt", "w+");
    err2 = fopen_s(&fp2, "Answers.txt", "w+");

    srand((unsigned long)time(0));

    //printf("-r");
    //scanf_s("%d", &r);
    //printf("-n");
    //scanf_s("%d", &n);

    //n不能简单作为循环的次数，要通过打印算术题的次数来判断n道题目。bug
    //题目的验证函数    
    while (i < 10) {
        sign = signal();
        arithmetic_fraction(sign, 20);
        i++;
    }

    if (fp1 == NULL || fp2 == NULL) {
        printf("文件不存在。\n");
    }
    else {
        while (i < n) {
            arithmetic_integer(signal(), r, fp1, fp2);
            i++;
        }
        fclose(fp1);
    }
    getchar();
    getchar();

    return 0;
}