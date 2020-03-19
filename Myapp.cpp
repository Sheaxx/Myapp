#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

//整数乘除的函数
char arithmetic_integer(char sign,int r,FILE*fp1,FILE *fp2) {
    int num1 = rand() % r;
    int num2 = rand() % r;
    //余数和倍数
    int remainder = 0, multiple = 0;
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

//分数加减的函数
/*char add_sub_fraction(char sign,int r) {
    int num1 = rand() % 10;
    int num2 = rand() % 20;
    int num3 = rand() % 10;
    int num4 = rand() % 20;
}
*/
void main() {
    FILE* fp1, * fp2;
    errno_t err1, err2;
    int i = 0;
    int n = 0, r = 0;//n控制生成题目数目，r控制题目中数值范围
    err1 = fopen_s(&fp1, "Exercises.txt", "w+");
    err2 = fopen_s(&fp2, "Answers.txt", "w+");
    srand((unsigned long)time(0));
    /*
    while (i < 10) {
        printf("%c", signal());
        i++;
    }
    */
    printf("-r");
    scanf_s("%d", &r);
    printf("-n");
    scanf_s("%d", &n);
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
}