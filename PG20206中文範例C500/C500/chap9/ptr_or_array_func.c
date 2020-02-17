#include <stdio.h>
#include <stdlib.h>

void sub2(int ptr[])
{
	int i;

	printf("sizeof %lu\n", sizeof(ptr));

	for (i = 0 ; i < 32 ; i++) {
		ptr[i] = 31 - i;
	}
}

void sub(int *ptr)
{
	int i;

	printf("sizeof %lu\n", sizeof(ptr));

	for (i = 0 ; i < 32 ; i++) {
		ptr[i] = i;
	}
}

int main(void)
{
	int data[32];
	int i;

	sub(data);
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	sub2(data);
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	return 0;
}

