#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int main(void)
{
	int i, val;

	srand(time(NULL));
	for (i = 0 ; i < 10 ; i++) {
//		val = rand() % MAX;
		val = ((1.0 / (RAND_MAX + 1.0)) * rand()) * MAX;
		printf("%d\n", val);
	}

	return 0;
}


