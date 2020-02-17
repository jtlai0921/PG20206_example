/*
 * label.c - [Local Label within the statement expression]
 */
#include <stdio.h>

int main(void)
{
	int i, j, n;
	int max = 10;

	({
	__label__ skip;
	for (i = 0 ; i < max ; i++) {
		for (j = 0 ; j < max ; j++) {
			n = i * j;
			if (n % 7 == 0)
				goto skip;
		}
	}
skip:;
	});

	if (max == 10)
		goto skip;

	return 0;
}

