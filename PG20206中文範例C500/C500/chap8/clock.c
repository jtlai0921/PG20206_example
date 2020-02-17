#include <stdio.h>
#include <time.h>

void sub(void)
{
	int i, j;

	for (i = 0 ; i < 10000 ; i++)
		for (j = 0 ; j < 100000 ; j++)
			;
}

int main(void)
{
	clock_t t;

	t = clock();

	sub();

	t = clock() - t;
	printf("°õ¦æ®É¶¡ %ld ¬í(%ld)\n", t/CLOCKS_PER_SEC, t);

	return 0;
}


