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

	/* ポインタ操作を誤ると… */
	for (i = 0 ; i < MAX ; i++) {
		printf("年?");
		scanf("%d", &entry[i].age);

		printf("名前?");
		scanf("%s", entry[i].name);

		printf("%s さんは %d 歳です\n", entry[i].name, entry[i].age);
	}

	_getch();  /* キー入力待ち */
	return 0;
}

