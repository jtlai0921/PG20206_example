#include <stdio.h>

int main(void)
{
	int m, n;
	int *p;

	m = 15;
	n = 5;
	p = &n;

	printf("%d / %d = %d\n", m, n, m / *p);
	//printf("%d / %d = %d\n", m, n, m/*p);

	return 0;
}

