#include <stdio.h>

int main(void)
{
	char *addr;
	unsigned long val;

	addr = (char *)0xdeadbeaf;
	val = (unsigned long)addr;

	printf("%p\n", addr);
	printf("%x\n", val);
	//printf("%c\n", *addr);

	return 0;
}

