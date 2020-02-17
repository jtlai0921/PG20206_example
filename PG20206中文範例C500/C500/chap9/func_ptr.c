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
	func_ptr_t ptr;
//	void (*ptr)(int);  // �]�i�H�w�q���o��

	ptr = foo;
	ptr(13);
	(*ptr)(17);

	ptr = bar;
	ptr(13);
	(*ptr)(17);

	return 0;
}

