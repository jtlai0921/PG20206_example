#include <stdio.h>

int main(void)
{
	char buf[32];

	printf("���������͂��Ă�������: ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		printf("%s", buf);
		printf("���������͂��Ă�������: ");
	}

	return 0;
}

