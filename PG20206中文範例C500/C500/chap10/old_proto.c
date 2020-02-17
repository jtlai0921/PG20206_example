/*
 * old_proto.c
 *
 */
#include <stdio.h>

void sub(short);

void sub(n)
	short n;
{
	printf("%d\n", n);
}


int main(void)
{
	sub(256);

	return 0;
}


