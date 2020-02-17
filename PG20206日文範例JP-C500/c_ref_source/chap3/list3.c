/*
 * list3.c - 「マクロが先か？コメントが先か？」
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

