/*
 * expression.c
 */
#include <stdio.h>

#define CAL(n) ({n++; n*=2; n;})

int main(void)
{
	int i, k;

	i = 10;
	k = CAL(i);
	printf("i %d k %d\n", i, k);

	return 0;
}

