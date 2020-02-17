#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *ptr;

	ptr = (void *)0;

	ptr = malloc(128);
	printf("%p\n", ptr);

	return 0;
}

