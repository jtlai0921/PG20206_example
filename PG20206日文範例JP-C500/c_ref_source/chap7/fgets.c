#include <stdio.h>

int main(void)
{
	char buf[32];

	printf("文字列を入力してください: ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		printf("%s", buf);
		printf("文字列を入力してください: ");
	}

	return 0;
}

