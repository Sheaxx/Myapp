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

//在题目数组e[]中拼接运算符
void signstrcat(char sign,char e[],int &k) {
    e[k++] = ' ';
    if (sign == '+' || sign == '-')e[k++] = sign;
    else {
        e[k++] = -95;
        if (sign == '*')e[k++] = -63;
        else e[k++] = -62;
    }
    e[k++] = ' ';
}

//生成运算数
int numcreate(int t[],int select,int r,char s[]) {
    int i = 0, sum = 0;;
    int choice = 0;
    int num0 = 0;
    if (select == 0) sum = 4;
    else if (select == 1)sum = 6;
    while (i < sum / 2 - 1) {
        s[i] = signal();
        i++;
    }
    
    if (select == 0)num0 = 0;
    else if (select == 1) {
        if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/')) {
            num0 = 2;//前括号
        }
        else if ((s[1] == '+' || s[1] == '-') && (s[0] == '*' || s[0] == '/')) {
            num0 = 3;//后括号
        }
        else num0 = 4;//不用加括号
    }

    i = 0;
    while (i < sum) {
        t[i++] = rand() % r;
        choice = rand() % 10;
        if (choice % 2 == 0)t[i++] = 1;//整数
        else t[i++] = random(r);//分数
    }
    return num0;
}

//整数除法的函数（判断分数是真分数、假分数、整数、0，并化简打印式子）
char division_integer(int numA, int numB, int tag,char e[],int &k,int str[]) {
    //余数和倍数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(numA, numB);

    //tag=1为第一个数，tag=2为后边的数，tag=3为答案
    //分子为0或分母为1
    if (numA == 0 || numB == 1) {
        if (tag == 1) {
            digit_integer(numA, e, k);
        }
        else if (tag == 2) {
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 3) {
            if (numA == 0) {
                str[0] = 0; str[1] = 0;
            }
            else {
                str[0] = numA;
                str[1] = 0;
            }
        }
        return 0;
    }
    //判断余数，能整除则返回除法答案
    else if (numA % numB == 0) {
        if (tag == 1) {
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 2) {
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 3) {
            str[0] = numA / numB; str[1] = 0;
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
            digit_integer(*p1, e, k);
            e[k++] = 39;
            digit_integer(*p2, e, k);
            e[k++] = '/';
            digit_integer(numB, e, k);
        }
        else if (tag == 2) {
            digit_integer(*p1, e, k);
            e[k++] = 39;
            digit_integer(*p2, e, k);
            e[k++] = '/';
            digit_integer(numB, e, k);
        }
        else if (tag == 3) {
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
            digit_integer(numA, e, k);
            e[k++] = '/';
            digit_integer(numB, e, k);
        }
        else if (tag == 2) {
            digit_integer(numA, e, k);
            e[k++] = '/';
            digit_integer(numB, e, k);
        }
        else if (tag == 3) {
            str[0] = 0;str[1] = numA; str[2] = numB;
        }
        return 2;
    }
}

//加减乘除函数
int arithmetic_fraction(int num[],char sign, int r, int &tag,char e[],int &k,int str[]) {
    int x = 0;
    
    if (sign == '-') {
        //对减的情况做判断，减数小于被减数则两者交换
        if (num[1] * num[4] - num[2] * num[3] < 0) {
            int t1, t2;
            t1 = num[3];
            num[3] = num[1];
            num[1] = t1;
            t2 = num[4];
            num[4] = num[2];
            num[2] = t2;
            //交换两个数后m1和m2也要交换
            //t3 = m2;
            //m2 = m1;
            //m1 = t3;
        }
    }

    if (sign == '/' && num[3] == 0) {
        num[3] = random(r);
        //m2 = max_common(num3, num4);
    }

    if (tag == 1)division_integer(num[1], num[2], tag, e, k, str);
    tag = 2;
    signstrcat(sign, e, k);
    x = k;
    division_integer(num[3], num[4], tag, e, k, str);

    if (sign == '+') {
        num[5] = num[1] * num[4] + num[3] * num[2];
        num[6] = num[2] * num[4];
        tag = 3;
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '-') {
        num[5] = num[1] * num[4] - num[3] * num[2];
        num[6] = num[2] * num[4];
        tag = 3;
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '*') {
        num[5] = num[1] * num[3];
        num[6] = num[2] * num[4];
        tag = 3;
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '/') {
        num[5] = num[1] * num[4];
        num[6] = num[2] * num[3];
        tag = 3;
        division_integer(num[5], num[6], tag, e, k, str);
    }
    return x;
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
    int i = 0, j = 0, k = 0, m = 0, x = 0, l = 0;
    int select1, select2;//随机选定分数或整数运算
    int n = 20, r = 5;//n控制生成题目数目，r控制题目中数值范围
    //tag=1是第一个数，tag=2是后边的数，tag=3是答案
    int tag = 1;
    int result;
    int num[7] = { 0 }, t[8] = { 0 };
    int str[3] = { 0 };//暂时存放分数的三部分
    char c[10] = { '\0' };//序号
    char s[3] = { '\0' };//运算符
    char e[100] = { '\0' };//题目
    char e1[50] = { '\0' };
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
            tag = 1;
            j = 0; k = 0; m = 0; x = 0; l = 0;
            select1 = rand() % 100;
            num[0] = numcreate(t, select1 % 2, r, s);
            if (num[0] == 0) {
                while (j < 4) {
                    num[j + 1] = t[j];
                    j++;
                }
                arithmetic_fraction(num, s[0], r, tag, e, k, str);
            }
            else if (num[0] == 2 || num[0] == 4) {
                while (j < 4) {
                    num[j + 1] = t[j];
                    j++;
                }
                if (num[0] == 2) {
                    e[k++] = '(';
                }
                arithmetic_fraction(num, s[0], r, tag, e, k, str);
                num[1] = num[5];
                num[2] = num[6];
                num[3] = t[4];
                num[4] = t[5];
                tag = 2;
                if (num[0] == 2) {
                    e[k++] = ')';
                }
                arithmetic_fraction(num, s[1], r, tag, e, k, str);
            }
            else if (num[0] == 3) {
                j = 1;
                while (j < 5) {
                    num[j] = t[j + 1];
                    j++;
                }
                e1[k++] = '(';
                arithmetic_fraction(num, s[1], r, tag, e1, k, str);
                e1[k++] = ')';
                num[1] = t[0];
                num[2] = t[1];
                num[3] = num[5];
                num[4] = num[6];
                tag = 1;
                k = 0;
                l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
                e[l] = '\0';
                strcat_s(e, e1);
                l = strlen(e);
                e[l] = '\0';
            }

            printf("%d. ", i + 1);
            printf("%s", e);
            digit_integer(i + 1, c, x);
            strcat_s(c, ".  ");//序号

            if (str[0] == 0 && str[1] == 0) {
                digit_integer(0, a, m);
                printf(" = 0\n");
            }
            else if (str[0] != 0 && str[1] == 0) {
                digit_integer(str[0], a, m);
                printf(" = %d\n", str[0]);
            }
            else if (str[0] == 0 && str[1] != 0) {
                digit_integer(str[1], a, m);
                a[m++] = '/';
                digit_integer(str[2], a, m);
                printf(" = %d/%d\n", str[1], str[2]);
            }
            else {
                digit_integer(str[0], a, m);
                a[m++] = 39;//39是'的ASCII码
                digit_integer(str[1], a, m);
                a[m++] = '/';
                digit_integer(str[2], a, m);
                printf(" = %d'%d/%d\n", str[0], str[1], str[2]);
            }

            fputs(c, fp1);
            fputs(c, fp2);//写入序号
            fputs(e, fp1);//写入题目
            fputs(a, fp2);//写入答案
            fputc('\n', fp1);
            fputc('\n', fp2);
            j = 0; m = 0; x = 0;
            while (j<100) {
                e[j] = '\0';
                j++;
            }//重置题目字符数组
            while (m<50) {
                a[m] = '\0'; e1[m] = '\0';
                m++;
            }//重置答案字符数组
            while (x<10) {
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