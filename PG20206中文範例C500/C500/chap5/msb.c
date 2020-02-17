/*
 * msb.c
 */
#include <stdio.h>
#include <limits.h>

int main(void)
{
	char c;
	int msb;

	c = 0xff;
	msb = 1 << (sizeof(char)*CHAR_BIT-1);
	if (msb & c)
		printf("MSB = 1\n");
	else
		printf("MSB = 0\n");

	return 0;
}

