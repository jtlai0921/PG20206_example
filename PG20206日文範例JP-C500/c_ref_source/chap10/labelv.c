/*
 * labelv.c - [Labels as Values]
 */
#include <stdio.h>

int main(void)
{
	void *ptr;

	ptr = &&bar;
	goto *ptr;

foo:;
    printf("jump to foo label\n");

bar:;
    printf("jump to bar label\n");

	return 0;
}

