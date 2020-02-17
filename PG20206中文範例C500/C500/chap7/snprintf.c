#include <stdio.h>

int main(void)
{
	char buf[10];
	int y = 1976;

	_snprintf(buf, 8, "您是%d歲吧", 2003-y);
	buf[8] = '\0';
	printf("西元%d年生，也就是說%s\n", y, buf);

	return 0;
}

