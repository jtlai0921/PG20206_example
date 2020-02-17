/*
 * packed.c
 *
 */
#include <stdio.h>

struct foo {
	char x;
#ifdef TEST
	int y;
#else
	int y __attribute__ ((packed));
#endif
};

int main(void)
{
	struct foo hoge;

	printf("sizeof(char) = %d\n", sizeof(char));
	printf("sizeof(int) = %d\n", sizeof(int));

	printf("%d\n", sizeof(hoge));

	return 0;
}


