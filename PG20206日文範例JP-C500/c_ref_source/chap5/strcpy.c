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
	printf("�R�s�[�� %s\n", src);
	printf("�R�s�[�� %s\n", dst);
	printf("�Ԃ�l %s\n", ptr);

	ptr = strncpy(dst, "momo", 4);
	printf("�R�s�[�� %s\n", dst);
	printf("�Ԃ�l %s\n", ptr);

	ptr = strncpy(dst, "fufu", 5);
	printf("�R�s�[�� %s\n", dst);
	printf("�Ԃ�l %s\n", ptr);

	return 0;
}

