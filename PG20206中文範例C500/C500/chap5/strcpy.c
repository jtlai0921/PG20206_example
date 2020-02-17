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
	printf("複製來源 %s\n", src);
	printf("複製目標 %s\n", dst);
	printf("傳回值 %s\n", ptr);

	ptr = strncpy(dst, "momo", 4);
	printf("複製目標 %s\n", dst);
	printf("傳回值 %s\n", ptr);

	ptr = strncpy(dst, "fufu", 5);
	printf("複製目標 %s\n", dst);
	printf("傳回值 %s\n", ptr);

	return 0;
}

