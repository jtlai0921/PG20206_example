#include <stdio.h>

int main(void)
{
	char buf[128];
	int y = 1976;
	int i;

	sprintf(buf, "�z�O%d���a", 2003-y);
	printf("�褸%d�~�͡A�]�N�O��%s\n", y, buf);

	return 0;
}

