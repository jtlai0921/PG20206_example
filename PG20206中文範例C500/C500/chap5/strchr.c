/*
 * strchr.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *input = "A great book is great evil.";
	char *ptr;

	ptr = strchr(input, 'g');
	if (ptr)
		printf("found: %s\n", ptr);
	else
		printf("Not found\n");

	ptr = strrchr(input, 'g');
	if (ptr)
		printf("found: %s\n", ptr);
	else
		printf("Not found\n");

	return 0;
}

