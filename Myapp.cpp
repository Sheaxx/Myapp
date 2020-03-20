#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Myapp.h"

int count = 1;//题目和答案的序号

//生成运算符的函数
char signal() {
    int num = rand() % 100;
    int mod = num % 4;
    switch (mod) {
    case 0:return '+';
    //case 1:return '-';
    //case 2:return '*';
    //case 3:return '/';
    }
}

//拆分整数数位并存放进e[]
void digit_integer(int num,char e[],int &k){
    int j = 0;
    int d[50] = { 0 };
    while (num != 0) {
        d[j] = num % 10;
        num /= 10;
        j++;
    }//d[]用于暂时存放数位，注意是倒序的
    if (j == 0) {
        e[k] = '0';
        k++;
    }//如果num是0，则k指向e[]下一位
    else {
        j = j - 1;
        while (j >= 0) {
            e[k] = d[j] + 48;
            k++; j--;
        }
    }
}

//整数加减乘除的函数
char arithmetic_integer(char sign, int r,int num1,char e[],int &k) {
    int num2 = rand() % r;
    int num3 = random(r);  //分数的分母肯定不为0
    //int num1 = 12, num2 = 30;
    //倍数和余数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(num1, num2);

    //srand((unsigned long)time(0));
    if (sign == '+') {
        printf("%d. %d + %d = %d\n", count, num1, num2, num1 + num2);
        strcat_s(e, 5, " + ");
        k += 3;
        digit_integer(num2, e, k);
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
    else if (sign == '/') {
        //判断余数，能整除则直接打印
        if (num1 % num2 == 0) {
            printf("%d ÷ %d = %d\n", num1, num2, num1 / num2);
            return num1 / num2;
        }
        else if (num1 > num2) {
            remainder = num1 % num2;
            multiple = num1 / num2;
            printf("%d ÷ %d = %d'%d/%d\n", num1, num2, multiple, remainder, num2);
            return 0;
        }
        else if (num1 < num2) {
            printf("%d ÷ %d = %d/%d\n", num1, num2, num1, num2);
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
        return a / b;
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

//分数加减的函数
char add_sub_fraction(char sign, int r) {
    //分数1
    int num1 = rand() % 20;
    int num2 = random(r);
    //分数2
    int num3 = rand() % 20;
    int num4 = random(r);
    //分数结果
    int num5, num6;
    //倍数和余数
    int multiple1 = 0, remainder1 = 0, multiple2 = 0, remainder2 = 0;
    int* p1 = &multiple1, * p2 = &remainder1, * p3 = &multiple2, * p4 = &remainder2;
    //两个分数的最大公因数
    int m1 = max_common(num1, num2);
    int m2 = max_common(num3, num4);

    //判断两个分数是真分数、假分数、整数、0
    if (num1 % num2 == 0) {
        printf("%d + ", num1 / num2);
    }
    else if (num1 == 0 || num2 == 1) {
        printf("%d + ", num1);
    }
    else if (num1 > num2) {
        if (m1 == 1) {
            change(num1, num2, p1, p2);
            printf("%d'%d/%d + ", *p1, *p2, num2);
        }
        else {
            num1 = num1 / m1;
            num2 = num2 / m1;
            change(num1, num2, p1, p2);
            printf("%d'%d/%d + ", *p1, *p2, num2);
        }
    }
    else printf("%d/%d + ", num1, num2);

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
    else  printf("%d/%d", num3, num4);

    if (sign == '+') {
        num5 = num1 * num4 + num3 * num2;
        num6 = num2 * num4;
        division_integer(num5, num6);
    }

    return 0;
}

//假分数转化为带分数的函数
void change(int a, int b, int* mu, int* re) {
    //倍数，即带分数的整数部分
    *mu = a / b;
    //余数，即带分数的分数部分的分子
    *re = a % b;
    //带分数转化为m'r/b的真分数形式
}

//辗转相除法求最大公因数
int max_common(int m, int n) {
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
    while (num != 0)
        return num;
}

int main() {
    FILE* fp1, * fp2;
    errno_t err1, err2;
    int i = 0, j = 0, k = 0, m = 0, x = 0;
    int n = 0, r = 0;//n控制生成题目数目，r控制题目中数值范围
    int num1, result;
    int digit[10] = { 0 };//拆分数字每位数
    char sign = '+';
    char c[10] = { '\0' };//序号
    char e[50] = { '\0' };//题目
    char a[10] = { '\0' };//答案
    err1 = fopen_s(&fp1, "Exercises.txt", "a+");
    err2 = fopen_s(&fp2, "Answers.txt", "a+");

    srand((unsigned long)time(0));
   
    printf("-r");
    scanf_s("%d", &r);
    printf("-n");
    scanf_s("%d", &n);

    if (fp1 == NULL || fp2 == NULL) {
        printf("文件不存在。\n");
    }
    else {
        while (i < n) {
            j = 0; k = 0; m = 0; x = 0;
            num1 = rand() % 10;
            digit_integer(num1, e, k);
            digit_integer(arithmetic_integer('+', r, num1, e, k), a, m);
            digit_integer(count, c, x);
            strcat_s(c, ". ");
            fputs(c, fp1);
            fputs(c, fp2);
            fputs(e, fp1);
            fputs(a, fp2);
            fputc('\n', fp1);
            fputc('\n', fp2);
            count++;
            j = 0; m = 0; x = 0;
            while (e[j] != '\0') {
                e[j] = '\0';
                j++;
            }
            while (a[m] != '\0') {
                a[m] = '\0';
                m++;
            }
            while (c[x] != '\0') {
                c[x] = '\0';
                x++;
            }
            i++;
        }
        fclose(fp1);
        fclose(fp2);
    }
    getchar();
    getchar();
}