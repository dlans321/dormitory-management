#define _CRT_SECURE_NO_WARNINGS
#include"dormitory.h"

int intstr(char *buf, int buf_size, int num) //정수를 문자열로 변환
{
	int i = 0, count = 0, temp = num;

	while (num != 0) //count에 정수의 자릿수를 구함
	{
		num /= 10;
		count++;
	}
	num = temp;

	if (buf_size > count)
	{
		buf[count] = '\0';
		for (i = count - 1; i >= 0; i--)
		{
			buf[i] = (num % 10) + '0';
			num /= 10;
		}
		return 1;
	}
	return -1;
}

int first_semester(void) //1학기 파일 만드는 함수
{
	FILE *f, *w;
	char *file_name[4] = { " 1학기 관생.txt", " 년간 관생.txt", " 입사불가.txt", " 입사불가.txt" };
	char file_fullname[25] = { 0 };      //파일 풀네임
	time_t now = time(NULL);             //1970년부터 경과한 시간
	struct tm *today = localtime(&now);  //오늘 날짜

	int i = 0;            //반복제어변수
	char year[5] = { 0 }; //문자형 현재 년도

	w = fopen("파일 이름.txt", "w");
	if (w == NULL)
		return -1;

	intstr(year, sizeof(year), today->tm_year + 1900); //year에 현재 년도가 문자열로 저장

	for (i = 0; i <= 3; i++) //파일 풀네임을 만듬
	{
		if (i==3)
			intstr(year, sizeof(year), today->tm_year + 1901); //파일 풀네임을 다음 년도 합쳐서 만듬.

		strcpy(file_fullname, year); //year의 문자열 복사
		strcat(file_fullname, file_name[i]); //year의 문자열과 파일 이름이랑 합침 -> 풀네임
		f = fopen(file_fullname, "a");
		if (f == NULL)
			return -1;

		fclose(f);
		fprintf(w, "%s\n", file_fullname); //파일 풀네임을 파일 이름.txt에 저장
	}

	fclose(w);
	return 1;
}

int second_semester(void) //2학기 파일 만드는 함수
{
	FILE *f, *w;
	char *file_name[4] = { " 2학기 관생.txt", " 년간 관생.txt", " 입사불가.txt", " 입사불가.txt" };
	char file_fullname[25] = { 0 };      //파일 풀네임
	time_t now = time(NULL);             //1970년부터 경과한 시간
	struct tm *today = localtime(&now);  //오늘 날짜

	int i = 0;   //반복제어변수
	char year[5] = { 0 }; //문자형 현재 년도

	w = fopen("파일 이름.txt", "w");
	if (w == NULL)
		return -1;

	intstr(year, sizeof(year), today->tm_year + 1900); //year에 현재 년도가 문자열로 저장

	for (i = 0; i <= 3; i++) //파일 풀네임을 만듬
	{
		if (i == 3)
			intstr(year, sizeof(year), today->tm_year + 1901); //파일 풀네임을 다음 년도 합쳐서 만듬.

		strcpy(file_fullname, year); //year의 문자열 복사
		strcat(file_fullname, file_name[i]); //year의 문자열과 파일 이름이랑 합침 -> 풀네임
		f = fopen(file_fullname, "a");
		if (f == NULL)
			return -1;

		fclose(f);
		fprintf(w, "%s\n", file_fullname); //파일 풀네임을 파일 이름.txt에 저장
	}

	fclose(w);
	return 1;
}

int file_connection(FILE *f[], int size) //파일 연결하는 함수
{
	char line[50];
	int i = 0;
	int j = 0;

	if (size != 5)
		return -1;

	f[0] = fopen("파일 이름.txt", "r+");
	if (f[0] == NULL)
		return -1;

	for (i = 1; i < 5; i++)
	{
		if (fgets(line, 50, f[0]) == NULL)  //데이터를 못읽어오면 오류
		{
			return -1;
		}
		
		for (j = 0; j < sizeof(line); j++) //개행을 널 문자로 바꿔줌
		{
			if (line[j] == '\n')
				line[j] = '\0';
		}

		f[i] = fopen(line, "r+");  //파일 포인터의 배열에다가 파일 스트림 연결
		if (f[i] == NULL)
			return -1;
	}

	return 1;  //정상적인 종료
}

void nameform(char *buf)
{
	int i = 0;
	for (i = strlen(buf); i < 8; i++) //이름 형식 맟춤 널문자 포함 9바이트로
	{
		strcat(buf, " ");
	}
}

int input(FILE *f[], int size)
{
	char line[100] = { 0 }; //한 행
	resident temp = { 0 }; 
	time_t now = 0;         //시간
	struct tm *today = NULL;
	char living_time[30] = { 0 };  //주거 기간 (학기 or 년간)

	int second_semester = 0;        //1이면 2학기임을 알림
	int i = 0;                      //반복 제어변수
	int error = 0, number = 0;      //기타 변수

	if (size != 5)
		return -1;

	rewind(f[0]);
	fgets(line, sizeof(line), f[0]);
	sscanf(line, "%*s %s", line);    //line에 1학기 혹은 2학기 입력받음

	if (strcmp(line, "2학기") == 0)
		second_semester = 1;         //2학기임을 알림

	printf("학기/년간 학번 이름 호실을 입력해주세요. (종료는 x)\n");
	while (1)
	{
		printf("입력 : ");
		gets(line);

		if (strcmp(line, "x") == 0)  //x입력 하면 종료
		{
			puts("");
			break;
		}

		if (4 != sscanf(line, "%s %d %s %s", living_time, &temp.number, temp.name, temp.room)) 
		{
			printf("형식이 맞지 않습니다.\n\n");
			continue;
		}

		if (strcmp(living_time, "학기") != 0 && strcmp(living_time, "년간") != 0)
		{
			printf("학기 또는 년간을 입력해야됩니다.\n\n");
			continue;
		}

		if (second_semester == 1 && strcmp(living_time, "년간") == 0)  //2학기 년간 입력 x
		{
			printf("2학기는 년간 학생을 입력할 수 없습니다.\n\n");
			continue;
		}

		if (temp.number < 10000000 || temp.number > 99999999)
		{
			printf("학번은 8자리입니다.\n\n");
			continue;
		}

		if (strlen(temp.name) > 8)
		{
			printf("이름은 최대 4글자입니다.\n\n");
			continue;
		}

		if (strlen(temp.room) != 6)
		{
			printf("방 형식이 맞지 않습니다.\n\n");
			continue;
		}

		rewind(f[3]); //이번 년도 입사 불가자는 입력 x
		while (NULL != fgets(line, sizeof(line), f[3]))
		{
			sscanf(line, "%d", &number);
			if (number == temp.number)
			{
				error = -1;
				break;
			}
		}

		if (error == -1)
		{
			printf("이번 년도 입사 불가자는 입력이 불가능합니다.\n\n");
			error = 0;
			continue;
		}

		rewind(f[1]);  //학기에 이미 입력된 학번이면 입력 x
		while (NULL != fgets(line, sizeof(line), f[1]))
		{
			sscanf(line, "%d", &number);
			if (number == temp.number)
			{
				error = -1;
				break;
			}
		}

		if (error == -1)
		{
			printf("이미 입력된 학번입니다.\n\n");
			error = 0;
			continue;
		}

		rewind(f[2]); //년간에 이미 입력된 학번이면 입력 x
		while (NULL != fgets(line, sizeof(line), f[2]))
		{
			sscanf(line, "%d", &number);
			if (number == temp.number)
			{
				error = -1;
				break;
			}
		}

		if (error == -1)
		{
			printf("이미 입력된 학번입니다.\n\n");
			error = 0;
			continue;
		}

		if (second_semester == 1)
		{
			rewind(f[4]);
			while (NULL != fgets((line), sizeof(line), f[4]))
			{
				sscanf(line, "%d", &number);
				if (number == temp.number)
				{
					error = -1;
					break;
				}
			}
		}

		if (error == -1)
		{
			printf("다음 년도 입사불가 파일에 있는 학번입니다.\n");
			error = 0;
			continue;
		}


		nameform(temp.name);  //이름에 형식 맟춰줌 널문자 제외 8바이트
		now = time(NULL);
		today = localtime(&now);

		sprintf(line, "%02d %04d %02d %02d", 0, today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);

		if (strcmp(living_time, "학기") == 0)  //학기 파일에 입력
		{
			fseek(f[1], 0, SEEK_END);
			fprintf(f[1], "%d %s %s %s %s\n", temp.number, temp.name, temp.room, "입사상태", line);
		}
		else  //년간 파일에 입력
		{
			fseek(f[2], 0, SEEK_END);
			fprintf(f[2], "%d %s %s %s %s\n", temp.number, temp.name, temp.room, "입사상태", line);
		}
	}
	return 0;
}

int search_change(FILE *f[], int size)
{
	char line[100] = { 0 };
	int menu = 0, menu_error = 0, score = 0, living_time = 0; //메뉴 ,메뉴에러 ,점수 ,주거기간(0 - 학기, 1 - 년간)
	int error = 0;
	int success_searcing = 0;  //검색할 항목 찾으면 1
	int black_list = 0; //이번 년도 입사불가 파일에서 찾으면 1

	resident search_data = { 0 }; //찾는 데이터
	int number = 0; //검색할 학번
	int search_fpoint = 0; //찾는 데이터의 파일 포인터

	/*삭제에 필요한 변수들*/
	resident* delete_data = NULL;
	int row = 0;
	int i = 0;
	resident search_data2 = { 0 }; //찾는 데이터 2

	if (size != 5)
		return -1;

	while (1)
	{
		printf("검색/수정 하실 학번을 입력하세요(종료 x) :  ");
		gets(line);

		if (strcmp(line, "x") == 0)
		{
			puts("");
			break;
		}

		if (1 != sscanf(line, "%d", &number))
		{
			printf("학번을 다시 입력하세요.\n\n");
			continue;
		}

		if (number < 10000000 || number > 99999999)
		{
			printf("학번을 다시 입력하세요.\n\n");
			continue;
		}

		rewind(f[1]);  //학기 파일에다 비교
		while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
			&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
		{
			if (search_data.number == number)
			{
				printf("\n학기, %d(학번)  %s(이름)  %s(방번호)  %d(점수)\n%s  %d-%d-%d(입사날짜)\n", search_data.number, search_data.name,
					search_data.room, search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				search_fpoint = ftell(f[1]) - 49;  //찾는 데이터가 시작되는 파일 주소
				living_time = 0; //이 데이터는 학기에서 찾음
				success_searcing = 1; //해당 정보가 있으면 출력과 찾았다는 표시로 1를 넣어줌
				break;
			}
		}

		if (success_searcing == 0)   //학기 파일에서 못찾았으면 년간 파일에다 비교
		{
			rewind(f[2]); //년간 파일에다 비교
			while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
				&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
			{
				if (search_data.number == number)
				{
					printf("\n년간, %d(학번)  %s(이름)  %s(방번호)  %d(점수)\n%s  %d-%d-%d(입사날짜)\n", search_data.number, search_data.name, search_data.room,
						search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					search_fpoint = ftell(f[2]) - 49;
					living_time = 1; //이 데이터는 년간에서 찾음
					success_searcing = 1;
					break;
				}
			}
		}

		if (success_searcing == 0)
		{
			rewind(f[3]); //이번 년도 입사불가 파일에다 비교
			while (8 == fscanf(f[3], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
				&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
			{
				if (search_data.number == number)
				{
					printf("\n전년도, %d(학번)  %s(이름)  %s(방번호)  %d(점수)\n%s  %d-%d-%d(입사날짜)\n", search_data.number, search_data.name, search_data.room,
						search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					search_fpoint = ftell(f[3]) - 49;
					success_searcing = 1;
					black_list = 1;  //이번 년도 입사불가 파일에서 찾음
					break;
				}
			}
		}

		if (success_searcing == 0)
		{
			printf("없는 학번입니다.\n\n");
			continue;
		}
		success_searcing = 0;

		if (strcmp(search_data.situation, "강제퇴사") == 0)
		{
			printf("\n<1> 강제퇴사 해지 <2> 해지 안함 : ");
			
			menu_error = scanf("%d", &menu);
			fflush(stdin);

			if (menu < 1 || menu > 2 || menu_error != 1)
			{
				printf("메뉴 번호 입력 오류!\n\n");
			}

			if (menu == 2)
			{
				puts("");
				continue;
			}
	
			if (black_list == 1) //이번년도 입사 불가 파일에서 찾았으면
			{
				black_list = 0;
				rewind(f[0]);
				for (i = 0; i < 2; i++)   //파일에서 이번년도를 구해 파일명을 구함
				{
					fgets(line, sizeof(line), f[0]);
				}
				sscanf(line, "%s", line);
				strcat(line, " 입사불가.txt");

				fseek(f[3], 0, SEEK_END);
				row = ftell(f[3]) / 49; //행이 몇개인지

				if (row <= 0)
				{
					return -1;
				}

				if (row == 1) //행이 하나면 파일 다시 만듬
				{
					fclose(f[3]);
					f[3] = fopen(line, "w");
					if (f[3] == NULL)
					{
						return -1;
					}
					fclose(f[3]);
				}

				else
				{
					i = 0;
					delete_data = (resident *)malloc(sizeof(resident) * row - 1);

					if (delete_data == NULL)
					{
						return -1;
					}

					rewind(f[3]);
					while (8 == fscanf(f[3], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
						&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
					{
						if (search_fpoint == ftell(f[3]) - 49)  //같으면 삭제데이터니 데이터를 받으면안됨
							continue;

						delete_data[i++] = search_data;
					}

					fclose(f[3]);
					f[3] = fopen(line, "w");  //데이터를 다받고 이번년도 입사불가 파일을 새로열고 데이터를 씀
					if (f[3] == NULL)
					{
						return -1;
					}

					for (i = 0; i < row - 1; i++)
					{
						nameform(delete_data[i].name);
						fprintf(f[3], "%d %s %s %s %02d %04d %02d %02d\n", delete_data[i].number, delete_data[i].name, delete_data[i].room,
							delete_data[i].situation, delete_data[i].score, delete_data[i].come_in.year, delete_data[i].come_in.month, delete_data[i].come_in.day);
					}
					fclose(f[3]);
					free(delete_data);
				}

				f[3] = fopen(line, "r+");   
				if (f[3] == NULL)
					return -1;
			}

			else //다음년도 입사불가 파일에서 찾았으면
			{
				rewind(f[0]);
				for (i = 0; i < 4; i++)   //파일에서 다음년도를 구해 파일명을 구함
				{
					fgets(line, sizeof(line), f[0]);
				}
				sscanf(line, "%s", line);
				strcat(line, " 입사불가.txt");

				fseek(f[4], 0, SEEK_END);
				row = ftell(f[4]) / 49;

				if (row <= 0)
				{
					return -1;
				}

				if (row == 1)
				{
					fclose(f[4]);
					f[4] = fopen(line, "w");
					if (f[4] == NULL)
						return -1;
					fclose(f[4]);
				}

				else
				{
					i = 0;
					delete_data = (resident *)malloc(sizeof(resident) * row - 1);

					if (delete_data == NULL)
						return -1;

					fseek(f[4], 0, SEEK_SET);
					while (8 == fscanf(f[4], "%d %s %s %s %d %d %d %d\n", &search_data2.number, search_data2.name, search_data2.room, search_data2.situation,
						&search_data2.score, &search_data2.come_in.year, &search_data2.come_in.month, &search_data2.come_in.day))
					{
						if (search_data2.number != search_data.number)
						{
							delete_data[i++] = search_data2;
						}
					}

					fclose(f[4]);
					f[4] = fopen(line, "w");
					if (f[4] == NULL)
					{
						return -1;
					}

					for (i = 0; i < row - 1; i++)
					{
						nameform(delete_data[i].name);
						fprintf(f[4], "%d %s %s %s %02d %04d %02d %02d\n", delete_data[i].number, delete_data[i].name, delete_data[i].room,
							delete_data[i].situation, delete_data[i].score, delete_data[i].come_in.year, delete_data[i].come_in.month, delete_data[i].come_in.day);
					}
					fclose(f[4]);
					free(delete_data);
				}

				f[4] = fopen(line, "r+");
				if (f[4] == NULL)
					return -1;

				strcpy(search_data.situation, "입사상태");
				search_data.score = 0;

				nameform(search_data.name);
				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
			}
		}

		else
		{
			printf("\n<1>학번 수정 <2>이름 수정 <3>방번호 수정 <4> 점수 부여 <5> 입사 날짜 수정\n");
			printf("<6> 중간퇴사 설정 <7> 수정 안함 : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);

			if (menu < 1 || menu > 7 || menu_error != 1)
			{
				printf("메뉴 번호 입력 오류!\n\n");
				continue;
			}

			switch (menu)
			{
			case 1:
				printf("새 학번 입력 : ");

				menu_error = scanf("%d", &search_data.number);
				fflush(stdin);

				if (menu_error != 1)
				{
					printf("새 학번을 다시 입력하세요.\n");
					continue;
				}

				if (search_data.number < 10000000 || search_data.number > 99999999)
				{
					printf("새 학번을 다시 입력하세요.\n");
					continue;
				}

				rewind(f[3]); //이번 년도 입사 불가자는 입력 x
				while (NULL != fgets(line, sizeof(line), f[3]))
				{
					sscanf(line, "%d", &number);
					if (number == search_data.number)
					{
						error = -1;
						break;
					}
				}

				if (error == -1)
				{
					printf("입사 불가자의 학번입니다.\n");
					error = 0;
					continue;
				}

				rewind(f[1]);  //학기에 이미 입력된 학번이면 입력 x
				while (NULL != fgets(line, sizeof(line), f[1]))
				{
					sscanf(line, "%d", &number);
					if (number == search_data.number)
					{
						error = -1;
					}
				}

				if (error == -1)
				{
					printf("이미 존재하는 학번입니다.\n");
					error = 0;
					continue;
				}

				rewind(f[2]);  //년간 이미 입력된 학번이면 입력 x
				while (NULL != fgets(line, sizeof(line), f[2]))
				{
					sscanf(line, "%d", &number);
					if (number == search_data.number)
					{
						error = -1;
					}
				}

				if (error == -1)
				{
					printf("이미 존재하는 학번입니다.\n");
					error = 0;
					continue;
				}

				rewind(f[4]);
				while (NULL != fgets(line, sizeof(line), f[4]))
				{
					sscanf(line, "%d", &number);
					if (number == search_data.number)
					{
						error = -1;
					}
				}

				if (error == -1)
				{
					printf("다음 년도 입사 불가 파일에 있는 학번입니다.\n");
					error = 0;
					continue;
				}

				nameform(search_data.name); //이름 형식 맞춤

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);  //찾은 데이터의 처음으로가 덮어씀
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("수정 완료\n\n");
				break;

			case 2:
				printf("새이름 입력 : ");
				if (NULL == gets(search_data.name))
				{
					printf("새이름을 다시 입력하세요.\n");
					continue;
				}

				if (strlen(search_data.name) > 8)
				{
					printf("새이름을 다시 입력하세요.\n");
					continue;
				}

				nameform(search_data.name);

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("수정 완료\n\n");
				break;

			case 3:
				printf("새 방번호 입력 : ");
				if (NULL == gets(search_data.room))
				{
					printf("새 방번호를 다시 입력하세요.\n");
					continue;
				}

				if (strlen(search_data.room) != 6)
				{
					printf("새 방번호를 다시 입력하세요.\n");
					continue;
				}

				nameform(search_data.name);

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("수정 완료\n\n");
				break;

			case 4:
				if (strcmp(search_data.situation, "입사상태") != 0)
				{
					printf("퇴사자는 점수부여가 불가능합니다.\n\n");
					continue;
				}

				printf("부여할 점수 입력 : ");
				menu_error = scanf("%d", &score);
				fflush(stdin);

				if (1 != menu_error)
				{
					printf("부여 점수 다시 입력하세요.\n\n");
					continue;
				}

				if (score + search_data.score > 9)
				{
					printf("최대 상점은 9점입니다.\n\n");
					continue;
				}

				if (score + search_data.score < -9)
				{
					printf("최대 벌점은 -9점입니다.\n\n");
					continue;
				}

				search_data.score += score;

				nameform(search_data.name);

				if (search_data.score == -9)
				{
					strcpy(search_data.situation, "강제퇴사");
					fseek(f[4], 0, SEEK_END);  //벌점이 -9점이면 다음 년도 입사불가 txt에 저장
					fprintf(f[4], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				}

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("수정 완료\n\n");
				break;

			case 5:
				printf("새 입사날짜를 입력하세요 년 월 일 : ");
				gets(line);
				if (3 != sscanf(line, "%d %d %d", &search_data.come_in.year, &search_data.come_in.month,
					&search_data.come_in.day))
				{
					printf("새 입사날짜를 다시 입력하세요.\n\n");
					continue;
				}
				if ((search_data.come_in.year < 2000 || search_data.come_in.year > 9999) ||
					(search_data.come_in.month < 1 || search_data.come_in.month > 12) ||
					(search_data.come_in.day < 1 || search_data.come_in.day > 31))
				{
					printf("새 입사날짜를 다시 입력하세요.\n\n");
					continue;
				}

				nameform(search_data.name);
				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("수정 완료\n\n");
				break;

			case 6:
				if (strcmp(search_data.situation, "입사상태") == 0)
				{
					printf("중간퇴사로 설정하시겠습니까? <1> Yes <2> No : ");
					menu_error = scanf("%d", &menu);
					fflush(stdin);

					if (menu_error != 1)
					{
						printf("메뉴 번호 입력 오류!\n\n");
						continue;
					}

					if (menu == 2)
					{
						puts("");
						continue;
					}

					strcpy(search_data.situation, "중간퇴사");
					nameform(search_data.name);

					fseek(f[living_time + 1], search_fpoint, SEEK_SET);
					fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					printf("수정 완료\n\n");
					break;
				}

				else
				{
					printf("중간퇴사를 해지하시겠습니까? <1> Yes <2> No : ");

					menu_error = scanf("%d", &menu);
					fflush(stdin);

					if (menu_error != 1)
					{
						printf("메뉴 번호 입력 오류!\n\n");
						continue;
					}

					if (menu == 2)
					{
						puts("");
						continue;
					}

					printf("새 방번호를 입력하세요 : ");
					if (1 != scanf("%s", search_data.room))
					{
						fflush(stdin);
						printf("새 방번호를 다시 입력하세요.\n\n");
						continue;
					}
					fflush(stdin);

					if (strlen(search_data.room) != 6)
					{
						printf("새 방번호를 다시 입력하세요.\n\n");
						continue;
					}

					strcpy(search_data.situation, "입사상태");
					nameform(search_data.name);

					fseek(f[living_time + 1], search_fpoint, SEEK_SET);
					fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					printf("수정 완료\n\n");
					break;
				}
			default:
				puts("");
			}
		}
	}
	return 0;
}

int list_print(FILE *f[], int size)
{
	int menu = 0, menu_error = 0;
	int high_bonus_score = 6, high_minus_score = -6; //높은 상점과 벌점 기준점,  현 기준 6과 -6
	int max_bonus_score = 0, max_minus_score = 0; //최대 상점과 최대 벌점
	int min_number = 0, mmin_number = 0, count = 0, i = 0;
	int fpoint = 0, semester_year = 0; //(1- 학기, 2- 년간)
	resident temp = { 0 };

	if (size != 5)
		return -1;

	while (1)
	{
		printf("<1> 고상점 리스트 <2> 고벌점 리스트 <3> 이번년도 입사불가 리스트\n");
		printf("<4> 다음년도 입사불가 리스트 <5> 종료 : ");

		menu_error = scanf("%d", &menu);
		fflush(stdin);

		if (menu < 1 || menu > 5 || menu_error != 1)
		{
			printf("메뉴 번호 입력 오류!\n\n");
			continue;
		}

		if (menu == 5)
		{
			puts("");
			break;
		}

		switch (menu)
		{
		case 1:
			max_bonus_score = 0;
			fseek(f[1], 0, SEEK_SET);   //학기파일과 연간파일에서 max_bonus_score의 값을 구함
			while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				if (max_bonus_score < temp.score)
					max_bonus_score = temp.score;
			}

			fseek(f[2], 0, SEEK_SET);
			while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				if (max_bonus_score < temp.score)
					max_bonus_score = temp.score;
			}

			printf("\n고상점 리스트 출력 : \n");

			for (i = max_bonus_score; i >= high_bonus_score; i--)  //낮은 학번순과 높은 상점순으로 출력
			{
				min_number = 99999999;
				count = 0;

				fseek(f[1], 0, SEEK_SET);
				while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
					&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
				{
					if (temp.score == i && temp.number > mmin_number)
					{
						count++;
						if (temp.number < min_number)
						{
							min_number = temp.number;
							fpoint = ftell(f[1]) - 49;  //가장 작은 학번 데이터가 시작되는 파일포인터
							semester_year = 1;
						}
					}
				}

				fseek(f[2], 0, SEEK_SET);
				while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
					&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
				{
					if (temp.score == i && temp.number > mmin_number)
					{
						count++;
						if (temp.number < min_number)
						{
							min_number = temp.number;
							fpoint = ftell(f[2]) - 49;
							semester_year = 2; //가장 작은 학번이 년간에 있음을 알림
						}
					}
				}

				if (count >= 2) //즉 i가 계속 제자리이면
				{
					i++;
					mmin_number = min_number;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else if (count == 1) //다음 i로 넘어가면 mmin_number은 0
				{
					mmin_number = 0;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else //다음 i로 넘어가면 mmin_number은 0 출력은 안함
				{
					mmin_number = 0;
				}
			}
			puts(" ");
			break;

		case 2:
			max_minus_score = 0;

			fseek(f[1], 0, SEEK_SET);   //학기파일과 연간파일에서 max_minus_score의 값을 구함
			while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				if (max_minus_score > temp.score)
					max_minus_score = temp.score;
			}

			fseek(f[2], 0, SEEK_SET);
			while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				if (max_minus_score > temp.score)
					max_minus_score = temp.score;
			}

			printf("\n고벌점 리스트 출력 : \n");

			for (i = max_minus_score; i <= high_minus_score; i++)  //높은 벌점순과 낮은 학번순으로 출력
			{
				min_number = 99999999;
				count = 0;

				fseek(f[1], 0, SEEK_SET);
				while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
					&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
				{

					if (temp.score == i && temp.number > mmin_number)
					{
						count++;
						if (temp.number < min_number)
						{
							min_number = temp.number;
							fpoint = ftell(f[1]) - 49;
							semester_year = 1;
						}
					}
				}

				fseek(f[2], 0, SEEK_SET);
				while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
					&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
				{

					if (temp.score == i && temp.number > mmin_number)
					{
						count++;
						if (temp.number < min_number)
						{
							min_number = temp.number;
							fpoint = ftell(f[2]) - 49;
							semester_year = 2;
						}
					}
				}

				if (count >= 2) //즉 i가 계속 제자리이면
				{
					i--;
					mmin_number = min_number;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else if (count == 1) //다음 i로 넘어가면 mmin_number은 0
				{
					mmin_number = 0;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else //다음 i로 넘어가면 mmin_number은 0 출력은 안함
				{
					mmin_number = 0;
				}
			}
			puts("");
			break;

		case 3:   //이번년도 입사불가 리스트 출력

			rewind(f[0]);
			fscanf(f[0], "%d", &temp.come_in.year);
			printf("\n%d년도 입사불가 리스트 출력 : \n", temp.come_in.year);

			fseek(f[3], 0, SEEK_SET);
			while (8 == fscanf(f[3], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				printf("%d %-8s %s\n", temp.number, temp.name, temp.room);
			}
			puts("");
			break;

		case 4:  //다음년도 입사불가 리스트 출력

			rewind(f[0]);
			fscanf(f[0], "%d", &temp.come_in.year);
			printf("\n%d년도 입사불가 리스트 출력 : \n", temp.come_in.year + 1);

			fseek(f[4], 0, SEEK_SET);
			while (8 == fscanf(f[4], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				printf("%d %-8s %s\n", temp.number, temp.name, temp.room);
			}
			puts("");
			break;
		}
	}
	return 0;
}