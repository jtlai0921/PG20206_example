#include <stdio.h>

struct array {
	int a[32];
};

struct array sub(void)
{
	struct array arr;
	int i;

	for (i = 0 ; i < 32 ; i++) {
		arr.a[i] = i;
	}

	return (arr);
}

int main(void)
{
	struct array data;
	int *ptr, i;

	data = sub();
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", data.a[i]);
	}
	printf("\n");

	return 0;
}

