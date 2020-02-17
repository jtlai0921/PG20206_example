#include <stdio.h>
#include <math.h>

int main(void)
{
	double n;

	for (n = 0 ; n < 10 ; n++) {
		printf("ã%f = %f\n", n, sqrt(n));
	}

	return 0;
}

