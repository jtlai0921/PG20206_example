#include <stdio.h>
#include <stdlib.h>

int data[32];

void sub(int *ptr)
{
	int i;

	for (i = 0 ; i < 32 ; i++) {
		data[i] = i;
	}
	ptr = data;
}

int main(void)
{
	int *ptr = NULL;
	int i;

	printf("ptr %p\n", ptr);

	sub(ptr);

	printf("ptr %p\n", ptr);

	if (ptr) {
		for (i = 0 ; i < 32 ; i++) {
			printf("%d ", ptr[i]);
		}
	}

	return 0;
}

