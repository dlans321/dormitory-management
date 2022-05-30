#define _CRT_SECURE_NO_WARNINGS
#include"dormitory.h"

int main(void)
{
	FILE *f[5] = { NULL };
	int menu = 0, menu_error = 0, error = 0, i = 0;

	printf("����� ���� ���α׷��� ����˴ϴ�. �� �޴��� ��ȣ�� �Է��ϼ���.\n\n");

	while (1)
	{
		printf("<1> �Ի��� ���� �Է� <2> �Ի��� ���� ��ȸ/���� <3> ����Ʈ ��� <4> �Ի� ����\n");
		printf("<5> ���� : ");

		menu_error = scanf("%d", &menu); //������ �Է¹����� error�� 1
		fflush(stdin);
		if ((menu < 1 || menu > 5) || menu_error != 1)
		{
			printf("�޴� ��ȣ �Է� ����!\n\n");
			continue;
		}

		if (menu == 4)  //�޴��� 4�̸� ���� ����
		{
			printf("\n\n<1> 1�б� �Ի���� <2> 2�б� �Ի���� <3>�Ի� ���� : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);
			if ((menu < 1 || menu > 3) || menu_error != 1)
			{
				printf("�޴� ��ȣ �Է� ����!\n\n");
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
				printf("������ ���� ���α׷��� �����մϴ�.\n");
				return -1;
			}

			else
			{
				printf("������ �����Ǿ����ϴ�. �ٽ� �������ּ���.\n");
				return 0;
			}
		}
		break;  //�ݺ��� ����
	}

	error = file_connection(f, 5); //�޴��� 4�� �ƴϸ� ���Ͽ���
	if (error == -1)
	{
		printf("������ ���� ���α׷��� �����մϴ�.\n");
		return -1;
	}

	switch (menu) //�ѹ� ����
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
		printf("���α׷��� �����մϴ�.\n");
		return 0;
	}

	if (error == -1)
	{
		printf("������ ���� ���α׷��� �����մϴ�.\n");
	}

	while (1) //���� �ݺ� ����
	{
		printf("<1> �Ի��� ���� �Է� <2> �Ի��� ���� ��ȸ/���� <3> ����Ʈ ��� <4> �Ի� ����\n");
		printf("<5> ���� : ");

		error = scanf("%d", &menu); //������ �Է¹����� error�� 1
		fflush(stdin);
		if ((menu < 1 || menu > 5) || error != 1)
		{
			printf("�޴� ��ȣ �Է� ����!\n");
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
			printf("\n\n<1> 1�б� �Ի���� <2> 2�б� �Ի���� <3>�Ի� ���� : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);
			if ((menu < 1 || menu > 3) || menu_error != 1)
			{
				printf("�޴� ��ȣ �Է� ����!\n\n");
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
				printf("������ ���� ���α׷��� �����մϴ�.\n");
				return -1;
			}

			else
			{
				printf("������ �����Ǿ����ϴ�. �ٽ� �������ּ���.\n");
				return 0;
			}

		case 5:
			printf("\n\n");
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}

		if (error == -1)
		{
			printf("������ ���� ���α׷��� �����մϴ�.\n");
			return -1;
		}
	}
	return 0;
}