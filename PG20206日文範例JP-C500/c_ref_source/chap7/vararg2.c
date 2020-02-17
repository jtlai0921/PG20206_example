#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...)
{
	va_list args;
	int i, sum;

	va_start(args, count);
	sum = 0;
	for (i = 0 ; i < count ; i++) {
		sum += va_arg(args, int);
	}
	va_end(args);

	return (sum);
}

int main(void)
{
	int n;

	n = sum(3, 100, 101, 102);
	printf("%d\n", n);

	n = sum(-1, 100, 101, 102);
	printf("%d\n", n);

	n = sum(100);
	printf("%d\n", n);    /* •s’è */

	return 0;
}

