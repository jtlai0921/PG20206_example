#include <stdio.h>

int main(void)
{
	printf("file handle number %d\n", fileno(stdin));
	printf("file handle number %d\n", fileno(stdout));
	printf("file handle number %d\n", fileno(stderr));

	return 0;
}

