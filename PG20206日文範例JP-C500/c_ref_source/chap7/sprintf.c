#include <stdio.h>

int main(void)
{
	char buf[128];
	int y = 1976;
	int i;

	sprintf(buf, "%d�΂ł���", 2003-y);
	printf("����%d�N���܂�Ƃ������Ƃ�%s\n", y, buf);

	return 0;
}

