/*
 * strtol.c
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	long val;
	char *p;

	if (argc == 1)
		exit(1);

	val = strtol(argv[1], &p, 0);
	if (*p == '\0')
		printf("%ld\n", val);
	else
		printf("•ÏŠ·Ž¸”s (%s)\n", p);

	return 0;
}

