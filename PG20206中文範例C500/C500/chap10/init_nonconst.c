/*
 * init_nonconst.c
 *
 */
#include <stdio.h>

void sub(int a, int b)
{
	const int val = 255;
	int data[] = {10, a, b, a+b, val};
	int i;

	for (i = 0 ; i < sizeof(data)/sizeof(data[0]) ; i++) {
		printf("%d\n", data[i]);
	}
}

int main(void)
{
	sub(1, 2);

	return 0;
}

