/*
 * list4.c 
 *
 */
#include <stdio.h>

void sub(void)
{
	static int n = 0;
	int m = 0;

	n++;
	m++;
	printf("n %d m %d\n", n, m);
}

int main(void)
{
	sub();
	sub();
	sub();

	return 0;
}

