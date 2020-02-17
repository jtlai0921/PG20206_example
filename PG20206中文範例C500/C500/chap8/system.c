/* system.c */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ret;

	ret = system("type system.c");
	printf("ret %d\n", ret);

	return 0;
}

