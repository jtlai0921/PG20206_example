#include <stdio.h>

int main(void)
{
	char buf[128];
	int y = 1976;
	int i;

	sprintf(buf, "%d歳ですね", 2003-y);
	printf("西暦%d年生まれということは%s\n", y, buf);

	return 0;
}

