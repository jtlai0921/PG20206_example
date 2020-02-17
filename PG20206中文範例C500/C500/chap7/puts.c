#include <stdio.h>

int main(void)
{
	char *p;
	char *msg = "ABCDEFG";
	char *str = "ABC\0DEF";

	p = msg;
	while (*p) {
		putchar(*p);
		p++;
	}
	putchar('\n');

	puts(msg);
	puts(str);

	return 0;
}

