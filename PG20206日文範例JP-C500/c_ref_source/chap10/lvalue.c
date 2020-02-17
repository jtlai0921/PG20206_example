/*
 * lvalue.c
 */
#include <stdio.h>

int main(void)
{
	int x, y;

	x = y = 3;
	(x, y) += 5;

	printf("x %d y %d\n", x, y);

	return 0;
}

