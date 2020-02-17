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

	printf("˜AŒ‹‘O %s\n", dst);

	//strcat(ptr, src);      /* ‚±‚ê‚ÍNG */
	//strcat(ptr, 'A');      /* ‚±‚ê‚àNG */
	strcat(dst, src);

	printf("˜AŒ‹Œã %s\n", dst);

	return 0;
}

