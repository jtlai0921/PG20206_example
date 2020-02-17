/* macro_lines.c */
#include <stdio.h>

#define CHECK(n) { \
	if (n & 1) \ 
		n++; \
	else \
		n--; \
} \

int main(void)
{
	int i, k;

	for (i = 0 ; i < 5 ; i++) {
		k = i;
		CHECK(k);
		printf("%d -> %d\n", i , k);
	}

	return 0;
}

