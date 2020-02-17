/*
 * nestfunc.c
 */
#include <stdio.h>

int sub(int foo, int bar)
{
	int val;

	int sub2(int val) {
		return (val * 10 + foo + bar);
	}

	val = sub2(13);

	return (val);
}

int main(void)
{
	int ret;

	ret = sub(1, 2);
	printf("%d\n", ret);

	return 0;
}

