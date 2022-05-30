#define _CRT_SECURE_NO_WARNINGS
#include"dormitory.h"

int intstr(char *buf, int buf_size, int num) //������ ���ڿ��� ��ȯ
{
	int i = 0, count = 0, temp = num;

	while (num != 0) //count�� ������ �ڸ����� ����
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

int first_semester(void) //1�б� ���� ����� �Լ�
{
	FILE *f, *w;
	char *file_name[4] = { " 1�б� ����.txt", " �Ⱓ ����.txt", " �Ի�Ұ�.txt", " �Ի�Ұ�.txt" };
	char file_fullname[25] = { 0 };      //���� Ǯ����
	time_t now = time(NULL);             //1970����� ����� �ð�
	struct tm *today = localtime(&now);  //���� ��¥

	int i = 0;            //�ݺ������
	char year[5] = { 0 }; //������ ���� �⵵

	w = fopen("���� �̸�.txt", "w");
	if (w == NULL)
		return -1;

	intstr(year, sizeof(year), today->tm_year + 1900); //year�� ���� �⵵�� ���ڿ��� ����

	for (i = 0; i <= 3; i++) //���� Ǯ������ ����
	{
		if (i==3)
			intstr(year, sizeof(year), today->tm_year + 1901); //���� Ǯ������ ���� �⵵ ���ļ� ����.

		strcpy(file_fullname, year); //year�� ���ڿ� ����
		strcat(file_fullname, file_name[i]); //year�� ���ڿ��� ���� �̸��̶� ��ħ -> Ǯ����
		f = fopen(file_fullname, "a");
		if (f == NULL)
			return -1;

		fclose(f);
		fprintf(w, "%s\n", file_fullname); //���� Ǯ������ ���� �̸�.txt�� ����
	}

	fclose(w);
	return 1;
}

int second_semester(void) //2�б� ���� ����� �Լ�
{
	FILE *f, *w;
	char *file_name[4] = { " 2�б� ����.txt", " �Ⱓ ����.txt", " �Ի�Ұ�.txt", " �Ի�Ұ�.txt" };
	char file_fullname[25] = { 0 };      //���� Ǯ����
	time_t now = time(NULL);             //1970����� ����� �ð�
	struct tm *today = localtime(&now);  //���� ��¥

	int i = 0;   //�ݺ������
	char year[5] = { 0 }; //������ ���� �⵵

	w = fopen("���� �̸�.txt", "w");
	if (w == NULL)
		return -1;

	intstr(year, sizeof(year), today->tm_year + 1900); //year�� ���� �⵵�� ���ڿ��� ����

	for (i = 0; i <= 3; i++) //���� Ǯ������ ����
	{
		if (i == 3)
			intstr(year, sizeof(year), today->tm_year + 1901); //���� Ǯ������ ���� �⵵ ���ļ� ����.

		strcpy(file_fullname, year); //year�� ���ڿ� ����
		strcat(file_fullname, file_name[i]); //year�� ���ڿ��� ���� �̸��̶� ��ħ -> Ǯ����
		f = fopen(file_fullname, "a");
		if (f == NULL)
			return -1;

		fclose(f);
		fprintf(w, "%s\n", file_fullname); //���� Ǯ������ ���� �̸�.txt�� ����
	}

	fclose(w);
	return 1;
}

int file_connection(FILE *f[], int size) //���� �����ϴ� �Լ�
{
	char line[50];
	int i = 0;
	int j = 0;

	if (size != 5)
		return -1;

	f[0] = fopen("���� �̸�.txt", "r+");
	if (f[0] == NULL)
		return -1;

	for (i = 1; i < 5; i++)
	{
		if (fgets(line, 50, f[0]) == NULL)  //�����͸� ���о���� ����
		{
			return -1;
		}
		
		for (j = 0; j < sizeof(line); j++) //������ �� ���ڷ� �ٲ���
		{
			if (line[j] == '\n')
				line[j] = '\0';
		}

		f[i] = fopen(line, "r+");  //���� �������� �迭���ٰ� ���� ��Ʈ�� ����
		if (f[i] == NULL)
			return -1;
	}

	return 1;  //�������� ����
}

void nameform(char *buf)
{
	int i = 0;
	for (i = strlen(buf); i < 8; i++) //�̸� ���� ���� �ι��� ���� 9����Ʈ��
	{
		strcat(buf, " ");
	}
}

int input(FILE *f[], int size)
{
	char line[100] = { 0 }; //�� ��
	resident temp = { 0 }; 
	time_t now = 0;         //�ð�
	struct tm *today = NULL;
	char living_time[30] = { 0 };  //�ְ� �Ⱓ (�б� or �Ⱓ)

	int second_semester = 0;        //1�̸� 2�б����� �˸�
	int i = 0;                      //�ݺ� �����
	int error = 0, number = 0;      //��Ÿ ����

	if (size != 5)
		return -1;

	rewind(f[0]);
	fgets(line, sizeof(line), f[0]);
	sscanf(line, "%*s %s", line);    //line�� 1�б� Ȥ�� 2�б� �Է¹���

	if (strcmp(line, "2�б�") == 0)
		second_semester = 1;         //2�б����� �˸�

	printf("�б�/�Ⱓ �й� �̸� ȣ���� �Է����ּ���. (����� x)\n");
	while (1)
	{
		printf("�Է� : ");
		gets(line);

		if (strcmp(line, "x") == 0)  //x�Է� �ϸ� ����
		{
			puts("");
			break;
		}

		if (4 != sscanf(line, "%s %d %s %s", living_time, &temp.number, temp.name, temp.room)) 
		{
			printf("������ ���� �ʽ��ϴ�.\n\n");
			continue;
		}

		if (strcmp(living_time, "�б�") != 0 && strcmp(living_time, "�Ⱓ") != 0)
		{
			printf("�б� �Ǵ� �Ⱓ�� �Է��ؾߵ˴ϴ�.\n\n");
			continue;
		}

		if (second_semester == 1 && strcmp(living_time, "�Ⱓ") == 0)  //2�б� �Ⱓ �Է� x
		{
			printf("2�б�� �Ⱓ �л��� �Է��� �� �����ϴ�.\n\n");
			continue;
		}

		if (temp.number < 10000000 || temp.number > 99999999)
		{
			printf("�й��� 8�ڸ��Դϴ�.\n\n");
			continue;
		}

		if (strlen(temp.name) > 8)
		{
			printf("�̸��� �ִ� 4�����Դϴ�.\n\n");
			continue;
		}

		if (strlen(temp.room) != 6)
		{
			printf("�� ������ ���� �ʽ��ϴ�.\n\n");
			continue;
		}

		rewind(f[3]); //�̹� �⵵ �Ի� �Ұ��ڴ� �Է� x
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
			printf("�̹� �⵵ �Ի� �Ұ��ڴ� �Է��� �Ұ����մϴ�.\n\n");
			error = 0;
			continue;
		}

		rewind(f[1]);  //�б⿡ �̹� �Էµ� �й��̸� �Է� x
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
			printf("�̹� �Էµ� �й��Դϴ�.\n\n");
			error = 0;
			continue;
		}

		rewind(f[2]); //�Ⱓ�� �̹� �Էµ� �й��̸� �Է� x
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
			printf("�̹� �Էµ� �й��Դϴ�.\n\n");
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
			printf("���� �⵵ �Ի�Ұ� ���Ͽ� �ִ� �й��Դϴ�.\n");
			error = 0;
			continue;
		}


		nameform(temp.name);  //�̸��� ���� ������ �ι��� ���� 8����Ʈ
		now = time(NULL);
		today = localtime(&now);

		sprintf(line, "%02d %04d %02d %02d", 0, today->tm_year + 1900, today->tm_mon + 1, today->tm_mday);

		if (strcmp(living_time, "�б�") == 0)  //�б� ���Ͽ� �Է�
		{
			fseek(f[1], 0, SEEK_END);
			fprintf(f[1], "%d %s %s %s %s\n", temp.number, temp.name, temp.room, "�Ի����", line);
		}
		else  //�Ⱓ ���Ͽ� �Է�
		{
			fseek(f[2], 0, SEEK_END);
			fprintf(f[2], "%d %s %s %s %s\n", temp.number, temp.name, temp.room, "�Ի����", line);
		}
	}
	return 0;
}

int search_change(FILE *f[], int size)
{
	char line[100] = { 0 };
	int menu = 0, menu_error = 0, score = 0, living_time = 0; //�޴� ,�޴����� ,���� ,�ְűⰣ(0 - �б�, 1 - �Ⱓ)
	int error = 0;
	int success_searcing = 0;  //�˻��� �׸� ã���� 1
	int black_list = 0; //�̹� �⵵ �Ի�Ұ� ���Ͽ��� ã���� 1

	resident search_data = { 0 }; //ã�� ������
	int number = 0; //�˻��� �й�
	int search_fpoint = 0; //ã�� �������� ���� ������

	/*������ �ʿ��� ������*/
	resident* delete_data = NULL;
	int row = 0;
	int i = 0;
	resident search_data2 = { 0 }; //ã�� ������ 2

	if (size != 5)
		return -1;

	while (1)
	{
		printf("�˻�/���� �Ͻ� �й��� �Է��ϼ���(���� x) :  ");
		gets(line);

		if (strcmp(line, "x") == 0)
		{
			puts("");
			break;
		}

		if (1 != sscanf(line, "%d", &number))
		{
			printf("�й��� �ٽ� �Է��ϼ���.\n\n");
			continue;
		}

		if (number < 10000000 || number > 99999999)
		{
			printf("�й��� �ٽ� �Է��ϼ���.\n\n");
			continue;
		}

		rewind(f[1]);  //�б� ���Ͽ��� ��
		while (8 == fscanf(f[1], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
			&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
		{
			if (search_data.number == number)
			{
				printf("\n�б�, %d(�й�)  %s(�̸�)  %s(���ȣ)  %d(����)\n%s  %d-%d-%d(�Ի糯¥)\n", search_data.number, search_data.name,
					search_data.room, search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				search_fpoint = ftell(f[1]) - 49;  //ã�� �����Ͱ� ���۵Ǵ� ���� �ּ�
				living_time = 0; //�� �����ʹ� �б⿡�� ã��
				success_searcing = 1; //�ش� ������ ������ ��°� ã�Ҵٴ� ǥ�÷� 1�� �־���
				break;
			}
		}

		if (success_searcing == 0)   //�б� ���Ͽ��� ��ã������ �Ⱓ ���Ͽ��� ��
		{
			rewind(f[2]); //�Ⱓ ���Ͽ��� ��
			while (8 == fscanf(f[2], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
				&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
			{
				if (search_data.number == number)
				{
					printf("\n�Ⱓ, %d(�й�)  %s(�̸�)  %s(���ȣ)  %d(����)\n%s  %d-%d-%d(�Ի糯¥)\n", search_data.number, search_data.name, search_data.room,
						search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					search_fpoint = ftell(f[2]) - 49;
					living_time = 1; //�� �����ʹ� �Ⱓ���� ã��
					success_searcing = 1;
					break;
				}
			}
		}

		if (success_searcing == 0)
		{
			rewind(f[3]); //�̹� �⵵ �Ի�Ұ� ���Ͽ��� ��
			while (8 == fscanf(f[3], "%d %s %s %s %d %d %d %d\n", &search_data.number, search_data.name, search_data.room, search_data.situation,
				&search_data.score, &search_data.come_in.year, &search_data.come_in.month, &search_data.come_in.day))
			{
				if (search_data.number == number)
				{
					printf("\n���⵵, %d(�й�)  %s(�̸�)  %s(���ȣ)  %d(����)\n%s  %d-%d-%d(�Ի糯¥)\n", search_data.number, search_data.name, search_data.room,
						search_data.score, search_data.situation, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					search_fpoint = ftell(f[3]) - 49;
					success_searcing = 1;
					black_list = 1;  //�̹� �⵵ �Ի�Ұ� ���Ͽ��� ã��
					break;
				}
			}
		}

		if (success_searcing == 0)
		{
			printf("���� �й��Դϴ�.\n\n");
			continue;
		}
		success_searcing = 0;

		if (strcmp(search_data.situation, "�������") == 0)
		{
			printf("\n<1> ������� ���� <2> ���� ���� : ");
			
			menu_error = scanf("%d", &menu);
			fflush(stdin);

			if (menu < 1 || menu > 2 || menu_error != 1)
			{
				printf("�޴� ��ȣ �Է� ����!\n\n");
			}

			if (menu == 2)
			{
				puts("");
				continue;
			}
	
			if (black_list == 1) //�̹��⵵ �Ի� �Ұ� ���Ͽ��� ã������
			{
				black_list = 0;
				rewind(f[0]);
				for (i = 0; i < 2; i++)   //���Ͽ��� �̹��⵵�� ���� ���ϸ��� ����
				{
					fgets(line, sizeof(line), f[0]);
				}
				sscanf(line, "%s", line);
				strcat(line, " �Ի�Ұ�.txt");

				fseek(f[3], 0, SEEK_END);
				row = ftell(f[3]) / 49; //���� �����

				if (row <= 0)
				{
					return -1;
				}

				if (row == 1) //���� �ϳ��� ���� �ٽ� ����
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
						if (search_fpoint == ftell(f[3]) - 49)  //������ ���������ʹ� �����͸� ������ȵ�
							continue;

						delete_data[i++] = search_data;
					}

					fclose(f[3]);
					f[3] = fopen(line, "w");  //�����͸� �ٹް� �̹��⵵ �Ի�Ұ� ������ ���ο��� �����͸� ��
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

			else //�����⵵ �Ի�Ұ� ���Ͽ��� ã������
			{
				rewind(f[0]);
				for (i = 0; i < 4; i++)   //���Ͽ��� �����⵵�� ���� ���ϸ��� ����
				{
					fgets(line, sizeof(line), f[0]);
				}
				sscanf(line, "%s", line);
				strcat(line, " �Ի�Ұ�.txt");

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

				strcpy(search_data.situation, "�Ի����");
				search_data.score = 0;

				nameform(search_data.name);
				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
			}
		}

		else
		{
			printf("\n<1>�й� ���� <2>�̸� ���� <3>���ȣ ���� <4> ���� �ο� <5> �Ի� ��¥ ����\n");
			printf("<6> �߰���� ���� <7> ���� ���� : ");
			menu_error = scanf("%d", &menu);
			fflush(stdin);

			if (menu < 1 || menu > 7 || menu_error != 1)
			{
				printf("�޴� ��ȣ �Է� ����!\n\n");
				continue;
			}

			switch (menu)
			{
			case 1:
				printf("�� �й� �Է� : ");

				menu_error = scanf("%d", &search_data.number);
				fflush(stdin);

				if (menu_error != 1)
				{
					printf("�� �й��� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				if (search_data.number < 10000000 || search_data.number > 99999999)
				{
					printf("�� �й��� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				rewind(f[3]); //�̹� �⵵ �Ի� �Ұ��ڴ� �Է� x
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
					printf("�Ի� �Ұ����� �й��Դϴ�.\n");
					error = 0;
					continue;
				}

				rewind(f[1]);  //�б⿡ �̹� �Էµ� �й��̸� �Է� x
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
					printf("�̹� �����ϴ� �й��Դϴ�.\n");
					error = 0;
					continue;
				}

				rewind(f[2]);  //�Ⱓ �̹� �Էµ� �й��̸� �Է� x
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
					printf("�̹� �����ϴ� �й��Դϴ�.\n");
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
					printf("���� �⵵ �Ի� �Ұ� ���Ͽ� �ִ� �й��Դϴ�.\n");
					error = 0;
					continue;
				}

				nameform(search_data.name); //�̸� ���� ����

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);  //ã�� �������� ó�����ΰ� ���
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("���� �Ϸ�\n\n");
				break;

			case 2:
				printf("���̸� �Է� : ");
				if (NULL == gets(search_data.name))
				{
					printf("���̸��� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				if (strlen(search_data.name) > 8)
				{
					printf("���̸��� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				nameform(search_data.name);

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("���� �Ϸ�\n\n");
				break;

			case 3:
				printf("�� ���ȣ �Է� : ");
				if (NULL == gets(search_data.room))
				{
					printf("�� ���ȣ�� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				if (strlen(search_data.room) != 6)
				{
					printf("�� ���ȣ�� �ٽ� �Է��ϼ���.\n");
					continue;
				}

				nameform(search_data.name);

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("���� �Ϸ�\n\n");
				break;

			case 4:
				if (strcmp(search_data.situation, "�Ի����") != 0)
				{
					printf("����ڴ� �����ο��� �Ұ����մϴ�.\n\n");
					continue;
				}

				printf("�ο��� ���� �Է� : ");
				menu_error = scanf("%d", &score);
				fflush(stdin);

				if (1 != menu_error)
				{
					printf("�ο� ���� �ٽ� �Է��ϼ���.\n\n");
					continue;
				}

				if (score + search_data.score > 9)
				{
					printf("�ִ� ������ 9���Դϴ�.\n\n");
					continue;
				}

				if (score + search_data.score < -9)
				{
					printf("�ִ� ������ -9���Դϴ�.\n\n");
					continue;
				}

				search_data.score += score;

				nameform(search_data.name);

				if (search_data.score == -9)
				{
					strcpy(search_data.situation, "�������");
					fseek(f[4], 0, SEEK_END);  //������ -9���̸� ���� �⵵ �Ի�Ұ� txt�� ����
					fprintf(f[4], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				}

				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("���� �Ϸ�\n\n");
				break;

			case 5:
				printf("�� �Ի糯¥�� �Է��ϼ��� �� �� �� : ");
				gets(line);
				if (3 != sscanf(line, "%d %d %d", &search_data.come_in.year, &search_data.come_in.month,
					&search_data.come_in.day))
				{
					printf("�� �Ի糯¥�� �ٽ� �Է��ϼ���.\n\n");
					continue;
				}
				if ((search_data.come_in.year < 2000 || search_data.come_in.year > 9999) ||
					(search_data.come_in.month < 1 || search_data.come_in.month > 12) ||
					(search_data.come_in.day < 1 || search_data.come_in.day > 31))
				{
					printf("�� �Ի糯¥�� �ٽ� �Է��ϼ���.\n\n");
					continue;
				}

				nameform(search_data.name);
				fseek(f[living_time + 1], search_fpoint, SEEK_SET);
				fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
					search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
				printf("���� �Ϸ�\n\n");
				break;

			case 6:
				if (strcmp(search_data.situation, "�Ի����") == 0)
				{
					printf("�߰����� �����Ͻðڽ��ϱ�? <1> Yes <2> No : ");
					menu_error = scanf("%d", &menu);
					fflush(stdin);

					if (menu_error != 1)
					{
						printf("�޴� ��ȣ �Է� ����!\n\n");
						continue;
					}

					if (menu == 2)
					{
						puts("");
						continue;
					}

					strcpy(search_data.situation, "�߰����");
					nameform(search_data.name);

					fseek(f[living_time + 1], search_fpoint, SEEK_SET);
					fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					printf("���� �Ϸ�\n\n");
					break;
				}

				else
				{
					printf("�߰���縦 �����Ͻðڽ��ϱ�? <1> Yes <2> No : ");

					menu_error = scanf("%d", &menu);
					fflush(stdin);

					if (menu_error != 1)
					{
						printf("�޴� ��ȣ �Է� ����!\n\n");
						continue;
					}

					if (menu == 2)
					{
						puts("");
						continue;
					}

					printf("�� ���ȣ�� �Է��ϼ��� : ");
					if (1 != scanf("%s", search_data.room))
					{
						fflush(stdin);
						printf("�� ���ȣ�� �ٽ� �Է��ϼ���.\n\n");
						continue;
					}
					fflush(stdin);

					if (strlen(search_data.room) != 6)
					{
						printf("�� ���ȣ�� �ٽ� �Է��ϼ���.\n\n");
						continue;
					}

					strcpy(search_data.situation, "�Ի����");
					nameform(search_data.name);

					fseek(f[living_time + 1], search_fpoint, SEEK_SET);
					fprintf(f[living_time + 1], "%d %s %s %s %02d %04d %02d %02d\n", search_data.number, search_data.name, search_data.room,
						search_data.situation, search_data.score, search_data.come_in.year, search_data.come_in.month, search_data.come_in.day);
					printf("���� �Ϸ�\n\n");
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
	int high_bonus_score = 6, high_minus_score = -6; //���� ������ ���� ������,  �� ���� 6�� -6
	int max_bonus_score = 0, max_minus_score = 0; //�ִ� ������ �ִ� ����
	int min_number = 0, mmin_number = 0, count = 0, i = 0;
	int fpoint = 0, semester_year = 0; //(1- �б�, 2- �Ⱓ)
	resident temp = { 0 };

	if (size != 5)
		return -1;

	while (1)
	{
		printf("<1> ����� ����Ʈ <2> ����� ����Ʈ <3> �̹��⵵ �Ի�Ұ� ����Ʈ\n");
		printf("<4> �����⵵ �Ի�Ұ� ����Ʈ <5> ���� : ");

		menu_error = scanf("%d", &menu);
		fflush(stdin);

		if (menu < 1 || menu > 5 || menu_error != 1)
		{
			printf("�޴� ��ȣ �Է� ����!\n\n");
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
			fseek(f[1], 0, SEEK_SET);   //�б����ϰ� �������Ͽ��� max_bonus_score�� ���� ����
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

			printf("\n����� ����Ʈ ��� : \n");

			for (i = max_bonus_score; i >= high_bonus_score; i--)  //���� �й����� ���� ���������� ���
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
							fpoint = ftell(f[1]) - 49;  //���� ���� �й� �����Ͱ� ���۵Ǵ� ����������
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
							semester_year = 2; //���� ���� �й��� �Ⱓ�� ������ �˸�
						}
					}
				}

				if (count >= 2) //�� i�� ��� ���ڸ��̸�
				{
					i++;
					mmin_number = min_number;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else if (count == 1) //���� i�� �Ѿ�� mmin_number�� 0
				{
					mmin_number = 0;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else //���� i�� �Ѿ�� mmin_number�� 0 ����� ����
				{
					mmin_number = 0;
				}
			}
			puts(" ");
			break;

		case 2:
			max_minus_score = 0;

			fseek(f[1], 0, SEEK_SET);   //�б����ϰ� �������Ͽ��� max_minus_score�� ���� ����
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

			printf("\n����� ����Ʈ ��� : \n");

			for (i = max_minus_score; i <= high_minus_score; i++)  //���� �������� ���� �й������� ���
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

				if (count >= 2) //�� i�� ��� ���ڸ��̸�
				{
					i--;
					mmin_number = min_number;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else if (count == 1) //���� i�� �Ѿ�� mmin_number�� 0
				{
					mmin_number = 0;

					fseek(f[semester_year], fpoint, SEEK_SET);
					fscanf(f[semester_year], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
						&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day);

					printf("[%d] %d %-8s %s %s\n", temp.score, temp.number, temp.name, temp.room, temp.situation);
				}

				else //���� i�� �Ѿ�� mmin_number�� 0 ����� ����
				{
					mmin_number = 0;
				}
			}
			puts("");
			break;

		case 3:   //�̹��⵵ �Ի�Ұ� ����Ʈ ���

			rewind(f[0]);
			fscanf(f[0], "%d", &temp.come_in.year);
			printf("\n%d�⵵ �Ի�Ұ� ����Ʈ ��� : \n", temp.come_in.year);

			fseek(f[3], 0, SEEK_SET);
			while (8 == fscanf(f[3], "%d %s %s %s %d %d %d %d\n", &temp.number, temp.name, temp.room, temp.situation,
				&temp.score, &temp.come_in.year, &temp.come_in.month, &temp.come_in.day))
			{
				printf("%d %-8s %s\n", temp.number, temp.name, temp.room);
			}
			puts("");
			break;

		case 4:  //�����⵵ �Ի�Ұ� ����Ʈ ���

			rewind(f[0]);
			fscanf(f[0], "%d", &temp.come_in.year);
			printf("\n%d�⵵ �Ի�Ұ� ����Ʈ ��� : \n", temp.come_in.year + 1);

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