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

	printf("連結前 %s\n", dst);

	//strcat(ptr, src);      /* これはNG */
	//strcat(ptr, 'A');      /* これもNG */
	strcat(dst, src);

	printf("連結後 %s\n", dst);

	return 0;
}

