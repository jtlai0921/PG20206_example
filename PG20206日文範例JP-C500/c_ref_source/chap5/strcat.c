/*
 * strcat.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *src = "ijikuruna";
	char dst[128] = "hottaimo ";
	char *ptr = "hottaimo ";

	printf("�A���O %s\n", dst);

	//strcat(ptr, src);      /* �����NG */
	//strcat(ptr, 'A');      /* �����NG */
	strcat(dst, src);

	printf("�A���� %s\n", dst);

	return 0;
}

