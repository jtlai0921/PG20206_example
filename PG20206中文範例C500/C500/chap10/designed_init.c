/*
 * designed_init.c
 *
 */
#include <stdio.h>

int main(void)
{
	int data[10] = {
		[0] = -1,
		[1 ... 5] = 0,     // 1...5 is NG
		[6 ... 8] = 1,     // 6...8 is NG
	};
	int i;

	for (i = 0 ; i < 10 ; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}

