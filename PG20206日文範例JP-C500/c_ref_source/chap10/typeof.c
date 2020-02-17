/*
 * typeof.c
 */
#include <stdio.h>

#define SWAP(a, b) { \
	typeof(a) t; \
	t = a; \
	a = b; \
	b = t; \
}


int main(void)
{
	int m, n;

	m = 2003;
	n = 15;
	SWAP(m, n);
	printf("%d %d\n", m, n);

	return 0;
}

