#include <stdio.h>

int main(void)
{
	char buf[32];

	printf("�п�J�r��: ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		printf("%s", buf);
		printf("�п�J�r��: ");
	}

	return 0;
}

