#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fp;
	long size;

	if (argc == 1) {
		printf("help: filesize filename\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Can't open file\n");
		exit(1);
	}
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);

	printf("ファイルサイズ %ld バイト\n", size);

	fclose(fp);

	return 0;
}


