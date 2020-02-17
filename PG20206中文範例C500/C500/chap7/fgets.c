#include <stdio.h>

int main(void)
{
	char buf[32];

	printf("請輸入字串: ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		printf("%s", buf);
		printf("請輸入字串: ");
	}

	return 0;
}

