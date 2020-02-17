/*
 * arith_void.c
 *
 */
#include <stdio.h>

void sub(void)
{
	printf("sub() called\n");

}

int main(void)
{
	char n[] = {1, 2, 3, 0};
	void *ptr;

	ptr = &n;
	printf("%d\n", *(char *)ptr);
	ptr++;
	printf("%d\n", *(char *)ptr);

	return 0;
}

