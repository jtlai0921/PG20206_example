/*
 * var_array.c
 *
 */
#include <stdio.h>
#include <string.h>

void sub(char *str, int size)
{
	char a[strlen(str) + size];
	int i;

	printf("%d\n", sizeof(a));
}

int main(void)
{
	sub("foo", 10);

	return 0;
}

