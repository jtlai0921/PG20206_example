#include <stdio.h>

int main(void)
{
	char buf[10];
	int y = 1976;

	_snprintf(buf, 8, "%d歳になられるのですね", 2003-y);
	buf[8] = '\0';
	printf("西暦%d年生まれということは%s\n", y, buf);

	return 0;
}

