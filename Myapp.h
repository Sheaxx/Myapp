#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//����������ĺ���
char signal();
//�����Ӽ��˳��ĺ���
char arithmetic_integer(char sign, int r);
//���������ĺ���
char division_integer(int a, int b);
//�����Ӽ��˳��ĺ���
char arithmetic_fraction(char sign, int r);
//�ٷ���ת��Ϊ�������ĺ���
void change(int a, int b, int* m, int* r);
//շת��������������
int max_common(int m, int n);
//շת���������С������
int min_common(int m, int n);
//��ȡ��Ϊ0�������
int random(int r);