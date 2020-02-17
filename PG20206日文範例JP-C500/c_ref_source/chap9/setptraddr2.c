#include <stdio.h>

int main(void)
{
	char *addr;
	char val;
	char a[10];
	char *ptr = NULL;
	unsigned long n;

	addr = &val;
	printf("%p\n", addr);

	n = (unsigned long)&val;
	printf("%x\n", n);

	addr = a;
	printf("%p\n", addr);

	addr = ptr;
	printf("%p\n", addr);

	return 0;
}

