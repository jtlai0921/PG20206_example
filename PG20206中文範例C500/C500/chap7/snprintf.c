#include <stdio.h>

int main(void)
{
	char buf[10];
	int y = 1976;

	_snprintf(buf, 8, "�z�O%d���a", 2003-y);
	buf[8] = '\0';
	printf("�褸%d�~�͡A�]�N�O��%s\n", y, buf);

	return 0;
}

