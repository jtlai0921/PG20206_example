#include <stdio.h>

int main(void)
{
	char *s = "fuchu";

	printf("%s\n", s);
	s[0] = 'F';     /* 未定義の動作 */
	printf("%s\n", s);

	return 0;
}

