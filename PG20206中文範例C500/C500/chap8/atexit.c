#include <stdio.h>
#include <stdlib.h>

void sub3(void)
{
	puts("sub3()");
}

void sub2(void)
{
	puts("sub2()");
}

void sub1(void)
{
	puts("sub1()");
}

int main(void)
{
	atexit(sub1);
	atexit(sub2);
	atexit(sub3);

	puts("main()");

	return 0;
}

