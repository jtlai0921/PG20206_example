#include <stdio.h>

int main(void)
{
	char c = 'A';

	printf("%d\n", sizeof(char));
	printf("%d\n", sizeof('A'));
	printf("%x\n", c);

	return 0;
}

