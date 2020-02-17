/*
 * for.c
 */
#include <stdio.h>

int main(void)
{
	unsigned char c;

	for (c = 0 ; c < 256 ; c++) {
		printf("%d ", c);
	}

	/* come here? */

	return 0;
}

