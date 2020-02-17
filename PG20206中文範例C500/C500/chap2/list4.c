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

	/* 指標操作錯誤時… */
	for (i = 0 ; i < MAX ; i++) {
		printf("年齡？");
		scanf("%d", &entry[i].age);

		printf("名字？");
		scanf("%s", entry[i].name);

		printf("%s 先生/小姐是 %d 歲\n", entry[i].name, entry[i].age);
	}

	_getch();  /* 等待使用者輸入 */
	return 0;
}

