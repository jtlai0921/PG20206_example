#include <stdio.h>

int main(void)
{
	char buf[10];
	int y = 1976;

	_snprintf(buf, 8, "%d�΂ɂȂ���̂ł���", 2003-y);
	buf[8] = '\0';
	printf("����%d�N���܂�Ƃ������Ƃ�%s\n", y, buf);

	return 0;
}

