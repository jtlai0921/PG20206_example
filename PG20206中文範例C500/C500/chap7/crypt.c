#include <stdio.h>
#include <stdlib.h>

int key = 0xab;

int main(int argc, char **argv)
{
	FILE *fp, *fpout;
	int c;

	if (argc != 3) {
		printf("help: crypt input-file output-file\n");
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Can't open file\n");
		exit(1);
	}

	fpout = fopen(argv[2], "w");
	if (fpout == NULL) {
		printf("Can't create file\n");
		fclose(fp);
		exit(1);
	}

	while ((c = fgetc(fp)) != EOF) {
		fputc(c ^ key, fpout);
	}

	fclose(fpout);
	fclose(fp);

	return 0;
}


