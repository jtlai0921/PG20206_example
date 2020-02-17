/*
 * mixedcode.c
 */
#include <stdio.h>

int main(void)
{
	int i, num[10];

	for (i = 0 ; i < 10 ; i++) {
		num[i] = i*i*i;
	}

	int j;
	for (j = 0 ; j < 10 ; j++) {
		printf("%d ", num[j]);
	}
	printf("\n");

	return 0;
}

