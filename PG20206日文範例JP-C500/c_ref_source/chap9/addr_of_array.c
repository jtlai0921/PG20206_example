#include <stdio.h>

int main(void)
{
	int array[256];
	int *ptr;

	ptr = &array;  /* what? */

	printf("ptr %p\n", ptr);
	printf("array %p\n", array);
	printf("array[0] %p\n", &array[0]);

	return 0;
}

