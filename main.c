#define _CRT_SECURE_NO_WARNINGS
#include"dormitory.h"

int main(void)
{
	FILE *f[5] = { NULL };
	int menu = 0, menu_error = 0, error = 0, i = 0;

	printf("기숙사 관리 프로그램이 실행됩니다. 각 메뉴의 번호를 입력하세요.\n\n");

	while (1)
	{
		printf("<1> 입사자 정보 입력 <2> 입사자 정보 조회/수정 <3> 리스트 출력 <4> 입사 시작\n");
		printf("<5> 종료 : ");

		menu_error = scanf("%d", &menu); //정상적 입력받으면 error는 1
		fflush(stdin);
		if ((menu < 1 || menu > 5) || menu_error != 1)
		{
			printf("메뉴 번호 입력 오류!\n\n");
			continue;
		}

		if (menu == 4)  //메뉴가 4이면 파일 만듬
		{
			printf("\n\n<1> 1학기 입사시작 <2> 2학기 입사시작 <3>입사 안함 : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);
			if ((menu < 1 || menu > 3) || menu_error != 1)
			{
				printf("메뉴 번호 입력 오류!\n\n");
				continue;
			}

			if (menu == 1)
			{
				error = first_semester();
			}

			else if (menu == 2)
			{
				error = second_semester();
			}

			else
			{
				printf("\n");
				continue;
			}

			if (error == -1)
			{
				printf("오류로 인해 프로그램을 종료합니다.\n");
				return -1;
			}

			else
			{
				printf("파일이 생성되었습니다. 다시 실행해주세요.\n");
				return 0;
			}
		}
		break;  //반복문 종료
	}

	error = file_connection(f, 5); //메뉴가 4가 아니면 파일연결
	if (error == -1)
	{
		printf("오류로 인해 프로그램을 종료합니다.\n");
		return -1;
	}

	switch (menu) //한번 실행
	{
	case 1:
		printf("\n\n");
		input(f, 5);
		break;
	case 2:
		printf("\n\n");
		error = search_change(f, 5);
		break;
	case 3:
		printf("\n\n");
		list_print(f, 5);
		break;
	case 5:
		printf("\n\n");
		printf("프로그램을 종료합니다.\n");
		return 0;
	}

	if (error == -1)
	{
		printf("오류로 인해 프로그램을 종료합니다.\n");
	}

	while (1) //이제 반복 실행
	{
		printf("<1> 입사자 정보 입력 <2> 입사자 정보 조회/수정 <3> 리스트 출력 <4> 입사 시작\n");
		printf("<5> 종료 : ");

		error = scanf("%d", &menu); //정상적 입력받으면 error는 1
		fflush(stdin);
		if ((menu < 1 || menu > 5) || error != 1)
		{
			printf("메뉴 번호 입력 오류!\n");
			continue;
		}

		switch (menu)
		{
		case 1:
			printf("\n\n");
			input(f, 5);
			break;
		case 2:
			printf("\n\n");
			error = search_change(f, 5);
			break;
		case 3:
			printf("\n\n");
			list_print(f, 5);
			break;
		case 4:
			printf("\n\n<1> 1학기 입사시작 <2> 2학기 입사시작 <3>입사 안함 : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);
			if ((menu < 1 || menu > 3) || menu_error != 1)
			{
				printf("메뉴 번호 입력 오류!\n\n");
				continue;
			}

			if (menu == 1)
			{
				error = first_semester();
			}

			else if (menu == 2)
			{
				error = second_semester();
			}

			else
			{
				printf("\n");
				continue;
			}

			if (error == -1)
			{
				printf("오류로 인해 프로그램을 종료합니다.\n");
				return -1;
			}

			else
			{
				printf("파일이 생성되었습니다. 다시 실행해주세요.\n");
				return 0;
			}

		case 5:
			printf("\n\n");
			printf("프로그램을 종료합니다.\n");
			return 0;
		}

		if (error == -1)
		{
			printf("오류로 인해 프로그램을 종료합니다.\n");
			return -1;
		}
	}
	return 0;
}