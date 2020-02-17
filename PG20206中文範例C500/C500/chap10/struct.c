/*
 * struct.c - [tagged structure]
 *
 */
#include <stdio.h>

struct hoge {
	int foo;
	char bar;
	long zot;
};


int main(void)
{
	struct hoge body = {
		10, 'C', 123L,
	};

	struct hoge body2 = {
		foo:10, 
		bar:'C',
		zot:123L,
	};

	struct hoge body3 = {
		.foo = 10, 
		.bar = 'C',
		.zot = 123L,
	};

	printf("%d %c %ld\n", body.foo, body.bar, body.zot);
	printf("%d %c %ld\n", body2.foo, body2.bar, body2.zot);
	printf("%d %c %ld\n", body3.foo, body3.bar, body3.zot);

	return 0;
}


