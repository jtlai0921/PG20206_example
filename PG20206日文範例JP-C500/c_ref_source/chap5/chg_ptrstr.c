#include <stdio.h>

int main(void)
{
	char *s = "fuchu";

	printf("%s\n", s);
	s[0] = 'F';     /* ����`�̓��� */
	printf("%s\n", s);

	return 0;
}

