#include <stdio.h>

int *sub(void)
{
	int a[32];
	int i;

	for (i = 0 ; i < 32 ; i++) {
		a[i] = i;
	}

	return (a);
}

int main(void)
{
	int *ptr, i;

	ptr = sub();
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", ptr[i]);
	}
	printf("\n");

	return 0;
}

