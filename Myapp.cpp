#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Myapp.h"

//生成运算符的函数
char signal() {
    int num = rand() % 100;
    int mod = num % 4;
    switch (mod) {
    case 0:return '+';
    case 1:return '-';
    case 2:return '*';
    case 3:return '/';
    }
}

//拆分整数数位并存放进e[]
void digit_integer(int num, char e[], int& k) {
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
char arithmetic_integer(char sign, int r, int tag,int num1,char e[],int &k,int str[]) {
    int num2 = rand() % r;
    int num3 = random(r);  //分数的分母肯定不为0
    //倍数和余数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(num1, num2);

    //srand((unsigned long)time(0));

    if (sign == '+') {
        printf("%d + %d = %d\n", num1, num2, num1 + num2);
        strcat_s(e, 5, " + ");
        k += 3;
        digit_integer(num2, e, k);
        str[0] = num1 + num2;
        return num1 + num2;
    }
    else if (sign == '-') {
        if (num1 < num2) {//减法结果不能是负数
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }
        printf("%d - %d = %d\n", num1, num2, num1 - num2);
        strcat_s(e, 5, " - ");
        k += 3;
        digit_integer(num2, e, k);
        str[0] = num1 - num2;
        return num1 - num2;
    }
    else if (sign == '*') {
        printf("%d × %d = %d\n", num1, num2, num1 * num2);
        strcat_s(e, 5, " * ");
        k += 3;
        digit_integer(num2, e, k);
        str[0] = num1 * num2;
        return num1 * num2;
    }
    else if (sign == '/') {
        printf("%d ÷ %d",num1, num3);
        strcat_s(e, 5, " / ");
        k += 3;
        digit_integer(num3, e, k);
        tag = 3;
        division_integer(num1, num3, tag, sign, e, k, str);
    }
}

//整数除法的函数（判断分数是真分数、假分数、整数、0，并化简打印式子）
char division_integer(int numA, int numB, int tag, char sign,char e[],int &k,int str[]) {
    //余数和倍数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(numA, numB);

    //tag=1为第一个数，tag=2为后边的数，tag=3为答案
    //分子为0或分母为1
    if (numA == 0 || numB == 1) {
        if (tag == 1) {
            printf("%d", numA);
            digit_integer(numA, e, k);
        }
        else if (tag == 2) {
            if (sign == '+') {
                strcat_s(e, sizeof(" + ") + 10, " + ");
                printf(" + %d", numA / numB);
            }
            else if (sign == '-') {
                strcat_s(e, sizeof(" - ") + 10, " - ");
                printf(" - %d", numA / numB);
            }
            else if (sign == '*') {
                strcat_s(e, sizeof(" * ") + 10, " * ");
                printf(" × %d", numA / numB);
            }
            else if (sign == '/') {
                strcat_s(e, sizeof(" / ") + 10, " / ");
                printf(" ÷ %d", numA / numB);
            }
            k += 3;
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 3) {
            printf(" = %d\n", numA);
        }
        return 0;
    }
    //判断余数，能整除则返回除法答案
    else if (numA % numB == 0) {
        if (tag == 1) {
            printf("%d", numA / numB);
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 2) {
            if (sign == '+') {
                strcat_s(e, sizeof(" + ") + 10, " + ");
                printf(" + %d", numA / numB);
            }
            else if (sign == '-') {
                strcat_s(e, sizeof(" - ") + 10, " - ");
                printf(" - %d", numA / numB);
            }
            else if (sign == '*') {
                strcat_s(e, sizeof(" * ") + 10, " * ");
                printf(" × %d", numA / numB);
            }
            else if (sign == '/') {
                strcat_s(e, sizeof(" / ") + 10, " / ");
                printf(" ÷ %d", numA / numB);
            }
            k += 3;
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 3) {
            printf(" = %d\n", numA / numB);
            str[0] = numA / numB;
        }
        return numA / numB;
    }
    //分子大于分母，是假分数，先化简再化为带分数，返回1
    else if (numA > numB) {
        //最大公因数为1，无需化简
        if (max != 1) {
            numA = numA / max;
            numB = numB / max; 
        }
        change(numA, numB, p1, p2);
        if (tag == 1) {
            printf("%d'%d/%d", *p1, *p2, numB);
            digit_integer(*p1, e, k);
            e[k] = 39;
            k++;
            digit_integer(*p2, e, k);
            e[k] = 47;
            k++;
            digit_integer(numB, e, k);
        }
        else if (tag == 2) {
            if (sign == '+') {
                strcat_s(e, sizeof(" + ") + 10, " + ");
                printf(" + %d'%d/%d", *p1, *p2, numB);
            }
            else if (sign == '-') {
                strcat_s(e, sizeof(" - ") + 10, " - ");
                printf(" - %d'%d/%d", *p1, *p2, numB);
            }
            else if (sign == '*') {
                strcat_s(e, sizeof(" * ") + 10, " * ");
                printf(" × %d'%d/%d", *p1, *p2, numB);
            }
            else if (sign == '/') {
                strcat_s(e, sizeof(" / ") + 10, " / ");
                printf(" ÷ %d'%d/%d", *p1, *p2, numB);
            }
            k += 3;
            digit_integer(*p1, e, k);
            e[k] = 39;
            k++;
            digit_integer(*p2, e, k);
            e[k] = 47;
            k++;
            digit_integer(numB, e, k);
        }
        else if (tag == 3) {
            printf(" = %d'%d/%d\n", *p1, *p2, numB);
            str[0] = *p1; str[1] = *p2; str[2] = numB;
        }
        return 1;
    }
    //分子小于分母，是真分数，只需要化简，返回2
    else if (numA < numB) {
        //最大公因数为1
        if (max != 1) {
            numA = numA / max;
            numB = numB / max;
        }
        if (tag == 1) {
            printf("%d/%d", numA, numB);
            digit_integer(numA, e, k);
            e[k] = 47;
            k++;
            digit_integer(numB, e, k);
        }
        else if (tag == 2) {
            if (sign == '+') {
                strcat_s(e, sizeof(" + ") + 10, " + ");
                printf(" + %d/%d", numA, numB);
            }
            else if (sign == '-') {
                strcat_s(e, sizeof(" - ") + 10, " - ");
                printf(" - %d/%d", numA, numB);
            }
            else if (sign == '*') {
                strcat_s(e, sizeof(" * ") + 10, " * ");
                printf(" × %d/%d", numA, numB);
            }
            else if (sign == '/') {
                strcat_s(e, sizeof(" / ") + 10, " / ");
                printf(" ÷ %d/%d", numA, numB);
            }
            k += 3;
            digit_integer(numA, e, k);
            e[k] = 47;
            k++;
            digit_integer(numB, e, k);
        }
        else if (tag == 3) {
            printf(" = %d/%d\n", numA, numB);
            str[1] = numA; str[2] = numB;
        }
        return 2;
    }
}

//分数加减乘除的函数
char arithmetic_fraction(char sign, int r, int tag,char e[],int k,int str[]) {
    //分数1
    int num1 = rand() % r;
    int num2 = random(r);
    //分数2
    int num3 = rand() % r;
    int num4 = random(r);
    //分数结果
    int num5, num6;

    if (sign == '-') {
        //对减的情况做判断，减数小于被减数则两者交换
        if (num1 * num4 - num2 * num3 < 0) {
            int t1, t2;
            t1 = num3;
            num3 = num1;
            num1 = t1;
            t2 = num4;
            num4 = num2;
            num2 = t2;
            //交换两个数后m1和m2也要交换
            //t3 = m2;
            //m2 = m1;
            //m1 = t3;
        }
    }
    if (sign == '/' && num3 == 0) {
        num3 = random(r);
        //m2 = max_common(num3, num4);
    }

    tag = 1;
    division_integer(num1, num2, tag, sign, e, k, str);
    e[k] = '\0';
    tag = 2;
    division_integer(num3, num4, tag, sign, e, k, str);
    e[k] = '\0';

    if (sign == '+') {
        num5 = num1 * num4 + num3 * num2;
        num6 = num2 * num4;
        tag = 3;
        division_integer(num5, num6, tag, sign, e, k, str);
    }
    else if (sign == '-') {
        num5 = num1 * num4 - num3 * num2;
        num6 = num2 * num4;
        if (num5 == 0)  printf(" = %d\n", 0);
        else {
            tag = 3;
            division_integer(num5, num6, tag, sign, e, k, str);
        }
    }
    else if (sign == '*') {
        num5 = num1 * num3;
        num6 = num2 * num4;
        if (num5 == 0)  printf(" = %d\n", 0);
        else {
            tag = 3;
            division_integer(num5, num6, tag, sign, e, k, str);
        }
    }
    else if (sign == '/') {
        num5 = num1 * num4;
        num6 = num2 * num3;
        if (num5 == 0)  printf(" = %d\n", 0);
        else {
            tag = 3;
            division_integer(num5, num6, tag, sign, e, k, str);
        }
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
    while (num == 0) {
        num = rand() % r;
    }
    return num;
}

int main() {
    FILE* fp1, * fp2;
    errno_t err1, err2;
    int i = 0, j = 0, k = 0, m = 0, x = 0;
    int select;//随机选定分数或整数运算
    int n = 20, r = 5;//n控制生成题目数目，r控制题目中数值范围
    //tag=1是第一个数，tag=2是后边的数，tag=3是答案
    int tag = 1;
    int num1, result;
    int str[3] = { 0 };//存放分数的三部分
    char c[10] = { '\0' };//序号
    char e[50] = { '\0' };//题目
    char a[50] = { '\0' };//答案
    err1 = fopen_s(&fp1, "Exercises.txt", "w+");
    err2 = fopen_s(&fp2, "Answers.txt", "w+");

    srand((unsigned long)time(0));

    //printf("-r");
    //scanf_s("%d", &r);
    //printf("-n");
    //scanf_s("%d", &n);

    //n不能简单作为循环的次数，要通过打印算术题的次数来判断n道题目。bug：排除重复的题目

    if (fp1 == NULL || fp2 == NULL) {
        printf("文件不存在。\n");
    }
    else {
        i = 0;
        while (i < n) {
            printf("%d. ", i + 1);
            j = 0; k = 0; m = 0; x = 0;
            select = rand() % 10;
            if (select % 2 == 1)arithmetic_fraction(signal(), r, tag, e, k, str);
            else {
                num1 = rand() % 10;
                digit_integer(num1, e, k);
                arithmetic_integer(signal(), r, tag, num1, e, k, str);
            }
            digit_integer(i + 1, c, x);
            strcat_s(c, ".  ");//序号
            if (str[0] != 0)digit_integer(str[0], a, m);
            if (str[1] != 0) {
                if (str[0] != 0) {
                    a[m] = 39;//39是'的ASCII码
                    m++;
                }
                digit_integer(str[1], a, m);
                a[m] = 47;//47是/的ASCII码
                m++;
                digit_integer(str[2], a, m);
            }
            if (str[0] == 0 && str[1] == 0)a[0] = 48;
            fputs(c, fp1);
            fputs(c, fp2);//写入序号
            fputs(e, fp1);//写入题目
            fputs(a, fp2);//写入答案
            fputc('\n', fp1);
            fputc('\n', fp2);
            j = 0; m = 0; x = 0;
            while (e[j] != '\0') {
                e[j] = '\0';
                j++;
            }//重置题目字符数组
            while (a[m] != '\0') {
                a[m] = '\0';
                m++;
            }//重置答案字符数组
            while (c[x] != '\0') {
                c[x] = '\0';
                x++;
            }//重置序号字符数组
            str[0] = str[1] = str[2] = 0;
            i++;
        }
        fclose(fp1);
        fclose(fp2);
    }

    getchar();
    getchar();

    return 0;
}