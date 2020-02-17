#include <stdio.h>

int main(void)
{
	char buf[128];
	int y = 1976;
	int i;

	sprintf(buf, "%dÎ‚Å‚·‚Ë", 2003-y);
	printf("¼—ï%d”N¶‚Ü‚ê‚Æ‚¢‚¤‚±‚Æ‚Í%s\n", y, buf);

	return 0;
}

