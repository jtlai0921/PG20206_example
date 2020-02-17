#include <stdio.h>

void sub(char *filename)
{
	FILE *fp;

	fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("Can't open %s file.\n", filename);
		return;
	}
	fclose(fp);
}

int main(void)
{
	sub("foo.txt");
	sub("foo bar.txt");

	if (remove("foo.txt")) {
		printf("Can't delete file\n");
	}

	return 0;
}

