/*
 * strcpy.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char src[] = "dodonpachi";
	char dst[128];
	char *ptr;

	ptr = strcpy(dst, src);
	printf("コピー元 %s\n", src);
	printf("コピー先 %s\n", dst);
	printf("返り値 %s\n", ptr);

	ptr = strncpy(dst, "momo", 4);
	printf("コピー先 %s\n", dst);
	printf("返り値 %s\n", ptr);

	ptr = strncpy(dst, "fufu", 5);
	printf("コピー先 %s\n", dst);
	printf("返り値 %s\n", ptr);

	return 0;
}

