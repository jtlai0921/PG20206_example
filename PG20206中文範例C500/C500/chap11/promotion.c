/* promotion.c */
#include <stdio.h>

int main(void)
{
	int i = -1;
	unsigned int n = 1;

	if (i > n)
		printf("i > n\n");
	else
		printf("i <= n\n");

	return 0;
}

