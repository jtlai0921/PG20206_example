/* main.c */
#include <stdio.h>

extern void sub(int);
extern void sub2(int);

int main(void)
{
	int n = 2003;

	printf("n = %d\n", n);

	sub(n);
	sub2(n);

	return 0;
}
