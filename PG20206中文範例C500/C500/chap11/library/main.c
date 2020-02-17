/*
 * main.c
 */
#include <stdio.h>
#include "isprime.h"

int main(void)
{
	int i;

	for (i = 0 ; i < 100 ; i++) {
		if (isprime(i))
			printf("%d\n", i);
	}

	return 0;
}

