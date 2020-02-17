/*
 * func_attr.c
 *
 */
#include <stdio.h>
#include <stdlib.h>

void terminate(void) __attribute__ ((noreturn));
void terminate(void)
{
	printf("program terminate\n");
	exit(1);
}

void sub(int val)
{
	printf("val %d\n", val);
}
void sub() __attribute__ ((stdcall));


int main(void)
{
	sub(0);
	terminate();

	return 0;
}

