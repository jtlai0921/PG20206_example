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

	printf("�s���e %s\n", dst);

	//strcat(ptr, src);      /* �o�ӬONG */
	//strcat(ptr, 'A');      /* �o�]�ONG */
	strcat(dst, src);

	printf("�s���� %s\n", dst);

	return 0;
}

