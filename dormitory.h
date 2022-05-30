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

struct resident //관생
{
	int number; //학번
	char name[10]; //이름
	char room[8]; //호실
	char situation[10]; //현재 상태 (입사중, 중간퇴사, 강제퇴사)
	int score; //점수
	date come_in; //입사 날짜
};
typedef struct resident resident;

/*4번 모집시작 메뉴 함수*/
int first_semester(void);  //1학기 파일 만듬
int second_semester(void); //2학기 파일 만듬

/*1번 입력 메뉴 함수*/
int input(FILE *f[], int size); //파일에다 입력하는 함수

/*2번 검색/수정 메뉴 함수*/
int search_change(FILE *f[], int size);

/*3번 리스트 출력 메뉴 함수*/
int  list_print(FILE *f[], int size);

/*각종 유틸리티 함수*/
int file_connection(FILE *f[], int size); //파일 연결
int intstr(char *buf, int buf_size, int num); //정수를 문자열로 변환
void nameform(char *buf); //이름 형식맞춤








#endif