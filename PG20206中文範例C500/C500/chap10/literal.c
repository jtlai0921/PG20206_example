/*
 * literal.c
 */
#include <stdio.h>

int main(void)
{
	char *str = "hello,
gcc
world!";

	printf("%s\n", str);

	return 0;
}

