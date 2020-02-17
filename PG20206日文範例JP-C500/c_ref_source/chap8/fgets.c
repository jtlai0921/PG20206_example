#include <stdio.h>

int main(void)
{
	char buf[128];
	int no;

	no = 0;
	do {
		no++;
		if (fgets(buf, sizeof(buf), stdin) != NULL)
			printf("%d: %s", no, buf);

	} while (feof(stdin) == 0);
	printf("no %d\n", no);

	return 0;
}

