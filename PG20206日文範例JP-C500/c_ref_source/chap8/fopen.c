#include <stdio.h>

int main(void)
{
	FILE *fp;
	char buf[128];
	int no;

	fp = fopen("eof.txt", "rb");
	if (fp == NULL)
		exit(1);

	no = 0;
	do {
		no++;
		if (fgets(buf, sizeof(buf), fp) != NULL)
			printf("%d: %s", no, buf);

	} while (feof(fp) == 0);
	printf("no %d\n", no);

	fclose(fp);

	return 0;
}

