/*
 * list3.c - �u�}�N�����悩�H�R�����g���悩�H�v
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

