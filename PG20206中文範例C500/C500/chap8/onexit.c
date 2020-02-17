#include <stdio.h>
#include <stdlib.h>

long argument;

void sub(int status, void *arg)
{
	long val = *(long *)arg;
	
	printf("sub(): status %d *arg %ld\n", status, val);
}

int main(void)
{
	on_exit(sub, &argument);

	argument = 13;
	puts("main()");
	exit(3);

	return 0;
}

