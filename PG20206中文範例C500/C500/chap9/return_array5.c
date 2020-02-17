#include <stdio.h>
#include <stdlib.h>

void sub(int arr[])
{
	int i;

	for (i = 0 ; i < 32 ; i++) {
		arr[i] = i;
	}
}

int main(void)
{
	int ptr[32];
	int i;

	sub(ptr);
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", ptr[i]);
	}
	printf("\n");

	return 0;
}

