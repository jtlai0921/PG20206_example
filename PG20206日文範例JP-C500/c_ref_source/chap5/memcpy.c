/*
 * memcpy.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	int n = 1;
	char endian;
	int *ptr = &n;
	void *addr;

	/* copy pointer-address */
	memcpy(&addr, &ptr, sizeof(void *));
	printf("%p %p\n", ptr, addr);

	/* check endian */
	memcpy(&endian, &n, 1);
	printf("%s endian\n", endian ? "little" : "big");

	return 0;
}

