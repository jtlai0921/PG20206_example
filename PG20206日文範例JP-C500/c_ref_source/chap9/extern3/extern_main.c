/*
 * extern_main.c
 */
#include <stdio.h>

/* ‚±‚¤‚·‚é‚Æ—Ž‚¿‚Ü‚· */
extern int *data;

int main(void)
{
	int i;

	printf("%p\n", data);

	for (i = 0 ; i < 26 ; i++) {
		data[i] = 'A' + i;
		printf("%c ", data[i]);
	}
	printf("\n");

	return 0;
}

