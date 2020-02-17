#include <stdio.h>
#include <string.h>

int main(void)
{
	FILE *fp;

	fp = fopen("foo.txt", "r");
	if (fp == NULL) {
		printf("errno %d\n", errno);

	}

	return 0;
}

