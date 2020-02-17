/*
 * var_macro.c
 */
#include <stdio.h>

#if 1
#define DBGPRINT(msg, ...) printf(msg, ## __VA_ARGS__)
#else
#define DBGPRINT(msg, ...) (void)(msg, ## __VA_ARGS__)
#endif


int main(void)
{
	printf("hello, world\n");
	DBGPRINT("hello, gcc world\n");
	DBGPRINT("hello, %s world\n", "Linux");

	return 0;
}

