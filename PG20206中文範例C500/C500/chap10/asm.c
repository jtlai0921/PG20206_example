/*
 * asm.c
 */
#include <stdio.h>

int main(void)
{
	int a, b;

	a = 10;
	b = 3;

	asm volatile (
		"xorl %0, %1\n\t"
		"xorl %1, %0\n\t"
		"xorl %0, %1"
		: : "a"(a), "b"(b));
	asm volatile ("movl %%eax, %0": "=m"(a));
	asm volatile ("movl %%ebx, %0": "=m"(b));

	printf("%d %d\n", a, b);

	return 0;
}

