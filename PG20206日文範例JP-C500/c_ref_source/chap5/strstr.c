/*
 * strstr.c
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>

int main(void)
{
	char *input = "Books and friends should be few but good.";
	char *ptr;
	ptrdiff_t len;

	ptr = strstr(input, "friend");
	if (ptr) {
		len = ptr - input;
		printf("%s\n", input);
		printf("%*s\n", len + 1, "^");
	} else {
		printf("Not found\n");
	}

	return 0;
}

