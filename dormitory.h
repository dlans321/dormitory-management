#ifndef ___dormitory____
#define ___dormitory____

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct date
{
	int year;
	int month;
	int day;
};
typedef struct date date;

struct resident //����
{
	int number; //�й�
	char name[10]; //�̸�
	char room[8]; //ȣ��
	char situation[10]; //���� ���� (�Ի���, �߰����, �������)
	int score; //����
	date come_in; //�Ի� ��¥
};
typedef struct resident resident;

/*4�� �������� �޴� �Լ�*/
int first_semester(void);  //1�б� ���� ����
int second_semester(void); //2�б� ���� ����

/*1�� �Է� �޴� �Լ�*/
int input(FILE *f[], int size); //���Ͽ��� �Է��ϴ� �Լ�

/*2�� �˻�/���� �޴� �Լ�*/
int search_change(FILE *f[], int size);

/*3�� ����Ʈ ��� �޴� �Լ�*/
int  list_print(FILE *f[], int size);

/*���� ��ƿ��Ƽ �Լ�*/
int file_connection(FILE *f[], int size); //���� ����
int intstr(char *buf, int buf_size, int num); //������ ���ڿ��� ��ȯ
void nameform(char *buf); //�̸� ���ĸ���








#endif