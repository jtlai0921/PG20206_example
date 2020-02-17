#include <stdio.h>

int main(void)
{
	char buf[128];
	int y = 1976;
	int i;

	sprintf(buf, "您是%d歲吧", 2003-y);
	printf("西元%d年生，也就是說%s\n", y, buf);

	return 0;
}

