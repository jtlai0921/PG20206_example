#include <stdio.h>

int main(void)
{
	float a, b;
	int m, n, sum;

	a = 1.234f;
	b = 1.567f;
	printf("%.3f\n", a + b);

	m = 1234;
	n = 1567;
	sum = m + n;
	printf("%d.%d\n", sum/1000, sum%1000);

	return 0;
}

