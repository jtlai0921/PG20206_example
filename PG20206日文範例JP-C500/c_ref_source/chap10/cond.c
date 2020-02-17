/* cond.c */
#include <stdio.h>

main()
{
	int n, ret;

	n = 2003;
	ret = (n ? n : n+1);
	printf("ret %d\n", ret);

	ret = (n ? : n+1);
	printf("ret %d\n", ret);
}

