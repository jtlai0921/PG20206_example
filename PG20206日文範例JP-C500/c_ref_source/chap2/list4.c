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

	/* �|�C���^��������Ɓc */
	for (i = 0 ; i < MAX ; i++) {
		printf("�N?");
		scanf("%d", &entry[i].age);

		printf("���O?");
		scanf("%s", entry[i].name);

		printf("%s ����� %d �΂ł�\n", entry[i].name, entry[i].age);
	}

	_getch();  /* �L�[���͑҂� */
	return 0;
}

