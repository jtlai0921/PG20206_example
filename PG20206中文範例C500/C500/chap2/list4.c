/* list4 */
#include <stdio.h>
#include <conio.h>

#define MAX 3

typedef struct data {
	int age;
	char *name;
} data_t;

int main(int argc, char **argv)
{
	data_t entry[MAX];
	int i;

	/* ���оާ@���~�ɡK */
	for (i = 0 ; i < MAX ; i++) {
		printf("�~�֡H");
		scanf("%d", &entry[i].age);

		printf("�W�r�H");
		scanf("%s", entry[i].name);

		printf("%s ����/�p�j�O %d ��\n", entry[i].name, entry[i].age);
	}

	_getch();  /* ���ݨϥΪ̿�J */
	return 0;
}

