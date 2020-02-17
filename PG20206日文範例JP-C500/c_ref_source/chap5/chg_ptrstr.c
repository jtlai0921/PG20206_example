#include <stdio.h>

int main(void)
{
	char *s = "fuchu";

	printf("%s\n", s);
	s[0] = 'F';     /* –¢’è‹`‚Ì“®ì */
	printf("%s\n", s);

	return 0;
}

