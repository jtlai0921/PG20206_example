/*
 * esc.c
 *
 */
#include <stdio.h>

int main(void)
{
	printf("\x1b[33m hello, world \x1b[m\n");
	printf("\e[33m hello, world \e[m\n");

	return 0;
}


