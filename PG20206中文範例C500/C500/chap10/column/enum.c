#include <stdio.h>

enum {
	A,
	B,
};

int main(void)
{
	int n = A;
	printf("%d\n", n);
	n = B;
	printf("%d\n", n);

	return 0;
}

