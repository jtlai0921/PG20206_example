#include <stdio.h>

int main(void)
{
	char **pptr;
	char *ptr;
	char n;

	n = 'A';
	ptr = &n;
	pptr = &ptr;

	//pptr = &&n;  /* �o�O���~����k */

	printf("ptr = %p\n", ptr);
	printf("pptr = %p\n", pptr);

	return 0;
}

