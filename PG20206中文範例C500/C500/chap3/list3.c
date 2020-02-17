/*
 * list3.c - 「是巨集先？還是註解先？」
 */
#include <stdio.h>

#define FOO(n) { \
	n++; \
	/* foo */ \
	n++; \
}

int main(void)
{
	int m = 0616;

	/* FOO(m); /* comment */

	printf("%d\n", m);

	return 0;
}

