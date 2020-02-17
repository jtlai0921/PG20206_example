#include <stdio.h>

int main(void)
{
	char cdata[128];
	char *cptr;
	int idata[128];
	int *iptr;

	cptr = cdata;
	printf("cptr %p\n", cptr);
	cptr++;
	printf("cptr %p\n", cptr);

	iptr = idata;
	printf("iptr %p\n", iptr);
	iptr++;
	printf("iptr %p\n", iptr);

	return 0;
}

