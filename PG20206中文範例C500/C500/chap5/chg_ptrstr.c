#include <stdio.h>

int main(void)
{
	char *s = "fuchu";

	printf("%s\n", s);
	s[0] = 'F';     /* ���w�q���ʧ@ */
	printf("%s\n", s);

	return 0;
}

