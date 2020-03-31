chu#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "Myapp.h"

int se = 0;
char list[10000][50] = { '\0' };

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
    e[k] = '\0';
}

//在题目数组e[]中拼接运算符
void signstrcat(char sign, char e[], int& k) {
    e[k++] = ' ';
    if (sign == '+' || sign == '-')e[k++] = sign;
    else {
        e[k++] = -95;
        if (sign == '*')e[k++] = -63;
        else e[k++] = -62;
    }
    e[k++] = ' ';
    e[k] = '\0';
}

//判断符号情况
int order(char s[], int select, int a) {
    int num0 = 0;
    if (select == 0)  num0 = 0;
    else if (select == 1) {
        if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/')) {
            if (a % 3 == 1)  num0 = 1;//前括号
            else if(a % 3 == 2)  num0 = 2;  //后括号
            else num0 = 5;//不加括号
        } 
        else if ((s[1] == '+' || s[1] == '-') && (s[0] == '*' || s[0] == '/')) {
            if (a % 3 == 1)  num0 = 1;//前括号
            else if (a % 3 == 2)  num0 = 2;  //后括号
            else num0 = 3;
        }
        else num0 = 3;//不用加括号 
    }
    else {
        if ((s[0] == '+' || s[0] == '-') && (s[1] == '+' || s[1] == '-') && (s[2] == '+' || s[2] == '-'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '*' || s[0] == '/') && (s[1] == '*' || s[1] == '/') && (s[2] == '*' || s[2] == '/'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '*' || s[0] == '/') && (s[2] == '+' || s[2] == '-'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/') && (s[2] == '+' || s[2] == '-'))
            num0 = 7;//先算中间两个数
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '+' || s[1] == '-') && (s[2] == '*' || s[2] == '/'))
            num0 = 8;//先算后面两个数
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/') && (s[2] == '*' || s[2] == '/'))
            num0 = 9;//先算后面三个数
        else if ((s[0] == '*' || s[0] == '/') && (s[1] == '+' || s[1] == '-') && (s[2] == '*' || s[2] == '/'))
            num0 = 10;//先算前后，再算中间
    }
    return num0;
}

//生成运算数
int numcreate(int t[], int select, int r, char s[]) {
    int i = 0, sum = 0;;
    int choice = 0;
    int a = rand() % 10;
    if (select == 0) sum = 4;
    else if (select == 1)  sum = 6;
    else if (select == 2)  sum = 8;
    while (i < sum / 2 - 1) {
        s[i] = signal();
        i++;
    }
    else {
        if ((s[0] == '+' || s[0] == '-') && (s[1] == '+' || s[1] == '-') && (s[2] == '+' || s[2] == '-'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '*' || s[0] == '/') && (s[1] == '*' || s[1] == '/') && (s[2] == '*' || s[2] == '/'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '*' || s[0] == '/') && (s[2] == '+' || s[2] == '-'))
            num0 = 6;//按顺序进行运算
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/') && (s[2] == '+' || s[2] == '-'))
            num0 = 7;//先算中间两个数
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '+' || s[1] == '-') && (s[2] == '*' || s[2] == '/'))
            num0 = 8;//先算后面两个数
        else if ((s[0] == '+' || s[0] == '-') && (s[1] == '*' || s[1] == '/') && (s[2] == '*' || s[2] == '/'))
            num0 = 9;//先算后面三个数
        else if ((s[0] == '*' || s[0] == '/') && (s[1] == '+' || s[1] == '-') && (s[2] == '*' || s[2] == '/'))
            num0 = 10;//先算前后，再算中间
    }

    i = 0;
    while (i < sum) {
        t[i++] = rand() % r;
        choice = rand() % 10;
        if (choice % 2 == 0)t[i++] = 1;//整数
        else t[i++] = random(r);//分数
    }

    /*t[0] = 2;
    t[1] = 1;
    t[2] = 1;
    t[3] = 4;
    t[4] = 9;
    t[5] = 4;*/

    return order(s, select, a);
}

//整数除法的函数（判断分数是真分数、假分数、整数、0，并化简打印式子）
char division_integer(int& numA, int& numB, int tag, char e[], int& k, int str[]) {
    //余数和倍数
    int multiple = 0, remainder = 0;
    int* p1 = &multiple, * p2 = &remainder;
    //最大公因数
    int max = max_common(numA, numB);

    //tag=1为第一个数，tag=2为后边的数，tag=3为答案
    //被除数为0，除法不存在
    if (numB == 0)  return -1;
    //分子为0或分母为1
    else if (numA == 0 || numB == 1) {
        if (tag == 1) {
            digit_integer(numA, e, k);
        }
        else if (tag == 2) {
            digit_integer(numA / numB, e, k);
        }
        else if (tag == 3) {
            if (numA == 0) {
                str[0] = 0;
                str[1] = 0;
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
            str[0] = 0; str[1] = numA; str[2] = numB;
        }
        return 2;
    }
}

//加减乘除函数
int arithmetic_fraction(int num[], char sign, int r, int& tag, char e[], int& k, int str[]) {
    int x = 0;

    if (sign == '-') {
        //对减的情况做判断，减数小于被减数则返回-1，不打印该式子
        if (num[1] * num[4] - num[2] * num[3] < 0)  return -1;
        /*if (num[1] * num[4] - num[2] * num[3] < 0) {
            int t1, t2;
            t1 = num[3];
            num[3] = num[1];
            num[1] = t1;
            t2 = num[4];
            num[4] = num[2];
            num[2] = t2;
        }*/
    }

    if (sign == '/' && num[3] == 0)  return -1;

    if (tag == 1)  division_integer(num[1], num[2], tag, e, k, str);
    tag = 2;
    signstrcat(sign, e, k);
    x = k;
    division_integer(num[3], num[4], tag, e, k, str);

    if (sign == '+') {
        num[5] = num[1] * num[4] + num[3] * num[2];
        num[6] = num[2] * num[4];
        tag = 3;
        //printf("+：%d+%d\n", num[5], num[6]);
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '-') {
        num[5] = num[1] * num[4] - num[3] * num[2];
        num[6] = num[2] * num[4];
        tag = 3;
        //printf("-：%d+%d\n", num[5], num[6]);
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '*') {
        num[5] = num[1] * num[3];
        num[6] = num[2] * num[4];
        tag = 3;
        //printf("*：%d+%d\n", num[5], num[6]);
        division_integer(num[5], num[6], tag, e, k, str);
    }
    else if (sign == '/') {
        num[5] = num[1] * num[4];
        num[6] = num[2] * num[3];
        tag = 3;
        //printf("/：%d+%d\n", num[5], num[6]);
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

//查找完全相同的题目
int repeat(char e[]) {
    int i = 0;
    do {
        if (strcmp(list[i], e) == 0)return -1;
        else i++;
    } while (strcmp(list[i], "\0") != 0);
    return 1;
}

//分析情况并写入文件
char* classify(int num[], int t[], char s[], int r, int i, FILE* fp1, FILE* fp2) {
    int j = 0, k = 0, m = 0, x = 0, l = 0;
    int tag = 1; //tag=1是第一个数，tag=2是后边的数，tag=3是答案
    int num1[7] = { 0 };
    int str[3] = { 0 };//暂时存放分数的三部分
    char c[10] = { '\0' };//序号
    char e[100] = { '\0' };//题目
    char e1[50] = { '\0' }, e2[50] = { '\0' };
    char a[20] = { '\0' };//答案
    char wrong[5] = "-1";

    if (num[0] == 0) {
        while (j < 4) {
            num[j + 1] = t[j];
            j++;
        }
        if (arithmetic_fraction(num, s[0], r, tag, e, k, str) == -1)
            return wrong;
    }
    else if (num[0] == 1 || num[0] == 3) {
        while (j < 4) {
            num[j + 1] = t[j];
            j++;
        }
        if (num[0] == 1) {
            e[k++] = '(';
        }
        if (arithmetic_fraction(num, s[0], r, tag, e, k, str) == -1)
            return wrong;
        num[1] = num[5];
        num[2] = num[6];
        num[3] = t[4];
        num[4] = t[5];
        tag = 2;
        if (num[0] == 1) {
            e[k++] = ')';
        }
        if (arithmetic_fraction(num, s[1], r, tag, e, k, str) == -1)
            return wrong;
    }
    else if (num[0] == 2 || num[0] == 5) {
        j = 1;
        while (j < 5) {
            num[j] = t[j + 1];
            j++;
        }
        e1[k++] = '(';
        if (arithmetic_fraction(num, s[1], r, tag, e1, k, str) == -1)
            return wrong;
        e1[k++] = ')';
        e1[k] = '\0';
        num[1] = t[0];
        num[2] = t[1];
        num[3] = num[5];
        num[4] = num[6];
        tag = 1;
        k = 0;
        l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
        if (l == -1)return wrong;
        e[l] = '\0';
        strcat_s(e, e1);
        l = strlen(e);
        e[l] = '\0';
    }
    else if (num[0] == 6) {
        while (j < 4) {
            num[j + 1] = t[j];
            j++;
        }
        if (arithmetic_fraction(num, s[0], r, tag, e, k, str) == -1)
            return wrong;
        num[1] = num[5];
        num[2] = num[6];
        num[3] = t[4];
        num[4] = t[5];
        tag = 2;
        if (arithmetic_fraction(num, s[1], r, tag, e, k, str) == -1)
            return wrong;
        num[1] = num[5];
        num[2] = num[6];
        num[3] = t[6];
        num[4] = t[7];
        tag = 2;
        if (arithmetic_fraction(num, s[2], r, tag, e, k, str) == -1)
            return wrong;
    }
    else if (num[0] == 7) {
        j = 1;
        while (j < 5) {
            num[j] = t[j + 1];
            j++;
        }
        if (arithmetic_fraction(num, s[1], r, tag, e1, k, str) == -1)
            return wrong;
        num[1] = t[0];
        num[2] = t[1];
        num[3] = num[5];
        num[4] = num[6];
        tag = 1;
        k = 0;
        l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
        if (l == -1)return wrong;
        e[l] = '\0';
        strcat_s(e, e1);
        k = l = strlen(e);
        e[l] = '\0';
        num[1] = num[5];
        num[2] = num[6];
        num[3] = t[6];
        num[4] = t[7];
        tag = 2;
        l = arithmetic_fraction(num, s[2], r, tag, e, k, str);
        if (l == -1)return wrong;
        e[k] = '\0';
    }
    else if (num[0] == 8 || num[0] == 10) {
        while (j < 4) {
            num1[j + 1] = t[j];
            j++;
        }
        j = 1;
        while (j < 5) {
            num[j] = t[j + 3];
            j++;
        }
        l = arithmetic_fraction(num1, s[0], r, tag, e1, k, str);
        if (l == -1)return wrong;
        k = 0;
        tag = 1;
        l = arithmetic_fraction(num, s[2], r, tag, e2, k, str);
        if (l == -1)return wrong;
        e[0] = '\0';
        strcat_s(e, e1);
        k = strlen(e);
        signstrcat(s[1], e, k);
        strcat_s(e, e2);
        num[1] = num1[5];
        num[2] = num1[6];
        num[3] = num[5];
        num[4] = num[6];
        k = 0;
        tag = 2;
        l = arithmetic_fraction(num, s[1], r, tag, e1, k, str);
        if (l == -1)return wrong;
    }
    else if (num[0] == 9) {
        j = 1;
        while (j < 5) {
            num[j] = t[j + 1];
            j++;
        }
        l = arithmetic_fraction(num, s[1], r, tag, e1, k, str);
        if (l == -1)return wrong;
        num[1] = num[5];
        num[2] = num[6];
        num[3] = t[6];
        num[4] = t[7];
        tag = 2;
        l = arithmetic_fraction(num, s[2], r, tag, e1, k, str);
        if (l == -1)return wrong;
        num[1] = t[0];
        num[2] = t[1];
        num[3] = num[5];
        num[4] = num[6];
        k = 0;
        tag = 1;
        l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
        if (l == -1)return wrong;
        e[l] = '\0';
        strcat_s(e, e1);
    }

    if (repeat(e) == -1)return wrong;
    else {
        strcpy_s(list[se], 50, e);
        se++;
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

    return a;
}

int main() {
    FILE* fp1, * fp2, * fp3, * fp4;
    errno_t err1, err2, err3, err4;
    int select = 0, select1 = 0;  //随机选定分数或整数运算
    int n = 20, r = 5;  //n控制生成题目数目，r控制题目中数值范围
    int i = 0, j = 0, k = 0, m = 0, p = 0, x = 0, a = 0;
    int y1 = 0, y2 = 0, y3 = 0;
    int mark = 0, tab = 0;
    int mo[4] = { 0 };
    int mi = 0;
    int num[7] = { 0 }, t[8] = { 0 };
    int c[100] = { 0 }, w[100] = { 0 };
    char s[10] = { '\0' };  //存放运算符
    char ef[100] = { '\0' };  //存放题目
    char af[20] = { '\0' };  //存放答案
    char cmp[20] = { '\0' };

    err1 = fopen_s(&fp1, "Exercises.txt", "w+");
    err2 = fopen_s(&fp2, "Answers.txt", "w+");
    err3 = fopen_s(&fp3, "exercisefile.txt", "r");
    err4 = fopen_s(&fp4, "answerfile.txt", "r");

    srand((unsigned long)time(0));

    if (fp1 == NULL || fp2 == NULL) {
        printf("文件不存在。\n");
    }
    else if (fp3 != NULL && fp4 != NULL) {
        while (fgets(ef, sizeof(ef) - 1, fp3) && fgets(af, sizeof(af) - 1, fp4)) {
            //获取题目和答案
            j = 0; k = 0; m = 0; p = 0; tab = 0; mark = 0;
            //y1 = 0; y2 = 0; y3 = 0;  //不需要初始化y2 y3
            while (j >= '0' && j <= '9')  j++;
            j += 4;//指到序号后的数字的第一位
            for (; j < strlen(ef); j++) {
                if (ef[j] >= '0' && ef[j] <= '9') {
                    if (mark == 0 || mark == 1) {
                        mi = ef[j] - 48;
                        t[k] = t[k] * 10 + mi;
                        if (ef[j + 1] == ' ' || ef[j + 1] == '\n' || ef[j + 1] == '\0' || ef[j + 1] == ')') {
                            if (mark == 0)t[++k] = 1;
                            else mark = 0;
                            k++;
                            if (k % 2 == 0 && k != 0)p++;
                        }
                        else if (ef[j + 1] == '/') {
                            mark = 1;
                            k++;
                        }
                        else if (ef[j + 1] == 39)mark = 2;
                    }
                    else if (mark == 2) {
                        mi = ef[j] - 48;
                        mo[p] = 10 * mo[p] + mi;
                        if (ef[j + 1] == '/') {
                            k++;
                            mark = 1;
                        }
                    }
                }
                else if (ef[j] == '+' || ef[j] == '-' || (ef[j] == -95 && (ef[j + 1] == -63 || ef[j + 1] == -62))) {
                    if (ef[j] == '+')s[m++] = '+';
                    else if (ef[j] == '-')s[m++] = '-';
                    else if (ef[j] == -95 && ef[j + 1] == -63)s[m++] = '*';
                    else s[m++] = '/';
                }
                else if (ef[j] == '(') {
                    if (k == 0)tab = 1;
                    else if (k == 2)tab = 2;
                }
                else if (ef[j] == ')') {
                    x = k;
                }
            }
            else if (num[0] == 6) {
                while (j < 4) {
                    num[j + 1] = t[j];
                    j++;
                }
                arithmetic_fraction(num, s[0], r, tag, e, k, str);
                num[1] = num[5];
                num[2] = num[6];
                num[3] = t[4];
                num[4] = t[5];
                tag = 2;
                arithmetic_fraction(num, s[1], r, tag, e, k, str);
                num[1] = num[5];
                num[2] = num[6];
                num[3] = t[6];
                num[4] = t[7];
                tag = 2;
                arithmetic_fraction(num, s[2], r, tag, e, k, str);
            }
            else if (num[0] == 7) {
                j = 1;
                while (j < 5) {
                    num[j] = t[j + 1];
                    j++;
                }
                arithmetic_fraction(num, s[1], r, tag, e1, k, str);
                num[1] = t[0];
                num[2] = t[1];
                num[3] = num[5];
                num[4] = num[6];
                tag = 1;
                k = 0;
                l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
                e[l] = '\0';
                strcat_s(e, e1);
                k = l = strlen(e);
                e[l] = '\0';
                num[1] = num[5];
                num[2] = num[6];
                num[3] = t[6];
                num[4] = t[7];
                tag = 2;
                arithmetic_fraction(num, s[2], r, tag, e, k, str);
                e[k] = '\0';
            }
            else if (num[0] == 8 || num[0] == 10) {
                while (j < 4) {
                    num1[j + 1] = t[j];
                    j++;
                }
                j = 1;
                while (j < 5) {
                    num[j] = t[j + 3];
                    j++;
                }
                arithmetic_fraction(num1, s[0], r, tag, e1, k, str);
                k = 0;
                tag = 1;
                arithmetic_fraction(num, s[2], r, tag, e2, k, str);
                strcat_s(e, e1);
                k = strlen(e);
                signstrcat(s[1], e, k);
                strcat_s(e, e2);
                num[1] = num1[5];
                num[2] = num1[6];
                num[3] = num[5];
                num[4] = num[6];
                k = 0;
                tag = 2;
                arithmetic_fraction(num, s[1], r, tag, e1, k, str);
            }
            else if (num[0] == 9) {
                j = 1;
                while (j < 5) {
                    num[j] = t[j + 1];
                    j++;
                }
                arithmetic_fraction(num, s[1], r, tag, e1, k, str);
                num[1] = num[5];
                num[2] = num[6];
                num[3] = t[6];
                num[4] = t[7];
                tag = 2;
                arithmetic_fraction(num, s[2], r, tag, e1, k, str);
                num[1] = t[0];
                num[2] = t[1];
                num[3] = num[5];
                num[4] = num[6];
                k = 0;
                tag = 1;
                l = arithmetic_fraction(num, s[0], r, tag, e, k, str);
                e[l] = '\0';
                strcat_s(e, e1);
            }

            for (m = 0, p = 0; m < k - 1; m += 2, p++) {
                if (mo[p] != 0)t[m] = t[m] * t[m + 1] + mo[p];
            }

            if (tab == 0) {
                //无括号
                if (k == 4)  select = 0;
                else if (k == 6) {
                    select = 1;
                    a = 3;
                }
                else if (k == 8)  select = 2;
            }
            else if (tab == 1) {
                //3个运算数，前括
                select = 1;
                a = 1;
            }
            else if (tab == 2) {
                //3个运算数，后括
                select = 1;
                a = 2;
            }
            /*else {
                select = 2;
                a = 1;
            }*/
            num[0] = order(s, select, a);
            digit_integer(i + 1, cmp, y3);
            cmp[y3++] = '.';
            cmp[y3++] = ' ';
            cmp[y3++] = ' ';
            cmp[y3++] = '\0';
            //y3 = strlen(cmp);
            cmp[strlen(cmp)] = '\0';
            strcat_s(cmp, 20, classify(num, t, s, r, i, fp1, fp2));
            y3 = strlen(cmp);
            cmp[y3] = '\n';  //换行符结尾
            cmp[++y3] = '\0';  //数组结尾
            if (strcmp(af, cmp) == 0)c[y1++] = i + 1;
            else w[y2++] = i + 1;
            for (j = 0; j < 8; j++) t[j] = 0;
            for (j = 0; j < 4; j++) mo[j] = 0;
            for (j = 0; j < 10; j++) s[j] = '\0';
            y3 = 0;
            i++;
        }
        fclose(fp3);
        fclose(fp4);

        //打印正确结果
        printf("Correct: %d (", y1);
        for (y3 = 0; y3 < y1 - 1; y3++)
            printf("%d，", c[y3]);
        printf("%d)\n", c[y3]);

        //打印错误结果
        printf("Wrong: %d (", y2);
        for (y3 = 0; y3 < y2 - 1; y3++)
            printf("%d，", w[y3]);
        printf("%d)\n", w[y3]);
    }
    else {
        while (i < n) {
            select1 = rand() % 30;
            num[0] = numcreate(t, select1 % 3, r, s);
            strcpy_s(cmp, classify(num, t, s, r, i, fp1, fp2));
            if (strcmp(cmp, "-1") == 0)continue;
            else i++;
        }
        fclose(fp1);
        fclose(fp2);
    }
    return 0;
}

