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
	printf("�ƻs�ӷ� %s\n", src);
	printf("�ƻs�ؼ� %s\n", dst);
	printf("�Ǧ^�� %s\n", ptr);

	ptr = strncpy(dst, "momo", 4);
	printf("�ƻs�ؼ� %s\n", dst);
	printf("�Ǧ^�� %s\n", ptr);

	ptr = strncpy(dst, "fufu", 5);
	printf("�ƻs�ؼ� %s\n", dst);
	printf("�Ǧ^�� %s\n", ptr);

	return 0;
}

