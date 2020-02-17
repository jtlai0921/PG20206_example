/*
 * unnamed.c
 *
 */
#include <stdio.h>

struct foo {
	int a;
	struct {
		int b;
		int c;
	};
	int d;
	int e;
};

int main(void)
{
	struct foo hoge;

	hoge.a = 0;
	hoge.b = 3;
	hoge.c = 7;
	hoge.e = 7;

	return 0;
}


