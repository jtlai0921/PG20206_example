/*
 * strlen.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *str[] = {
		"kira",
		"asuran\0zara",
		"‹@“®ím",
		"",
		0
	};
	char **p;

	p = str;
	while (*p) {
		printf("%s: %u\n", *p, strlen(*p));
		p++;
	}

	return 0;
}

