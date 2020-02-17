#include <stdio.h>

typedef void (*func_ptr_t)(int);

void bar(int n)
{
	printf("bar() %d\n", n*2);
}

void foo(int n)
{
	printf("foo() %d\n", n);
}

int main(void)
{
	func_ptr_t table[] = {
		foo,
		bar,
	};
	int i;

	for (i = 0 ; i < 2 ; i++) {
		table[i](100);
	}

	return 0;
}

