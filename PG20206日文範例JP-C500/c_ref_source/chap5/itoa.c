/*
 * itoa.c
 */
#include <stdio.h>

int main(void)
{
	char buf[128];
	int n;

	n = 2003;
	sprintf(buf, "%d", n);
	printf("%s\n", buf);

	sprintf(buf, "%x", n);
	printf("%s\n", buf);

	sprintf(buf, "%o", n);
	printf("%s\n", buf);

	return 0;
}

