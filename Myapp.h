#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//����������ĺ���
char signal();
//���������λ����Ž�e[]
void digit_integer(int num, char e[], int& k);
//����Ŀ����e[]��ƴ�������
void signstrcat(char sign, char e[], int& k);
//����������
int numcreate(int t[], int select, int r, char s[]);
//���������ĺ������жϷ�������������ٷ�����������0���������ӡʽ�ӣ�
char division_integer(int numA, int numB, int tag, char e[], int& k, int str[]);
//�Ӽ��˳�����
int arithmetic_fraction(int num[], char sign, int r, int& tag, char e[], int& k, int str[]);
//�ٷ���ת��Ϊ�������ĺ���
void change(int a, int b, int* m, int* r);
//շת��������������
int max_common(int m, int n);
//շת���������С������
int min_common(int m, int n);
//��ȡ��Ϊ0�������
int random(int r);