/*
 * ascii_code.c
 */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;

	for (c = 0 ; c < 256 ; c++) {
		if (c != 0 && c % 16 == 0)
			printf("\n");
		if (isprint(c)) {
			printf("%c ", c);
		} else {
			printf(". ");
		}
	}

	return 0;
}

