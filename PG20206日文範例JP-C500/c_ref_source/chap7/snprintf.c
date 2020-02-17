#include <stdio.h>

int main(void)
{
	char buf[10];
	int y = 1976;

	_snprintf(buf, 8, "%dçŒÇ…Ç»ÇÁÇÍÇÈÇÃÇ≈Ç∑ÇÀ", 2003-y);
	buf[8] = '\0';
	printf("êºóÔ%dîNê∂Ç‹ÇÍÇ∆Ç¢Ç§Ç±Ç∆ÇÕ%s\n", y, buf);

	return 0;
}

