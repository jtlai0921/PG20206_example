#include <stdio.h>

int main(void)
{
	char buf[128], week[16];
	int y, m, d;

	printf("¡“ú‚Ì“ú•t‚Æ—j“ú‚Í(YYYY/MM/HH —j“ú)H");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d/%d/%d %15s", &y, &m, &d, week);
//	sscanf(buf, "%d/%d/%d %s", &y, &m, &d, week);

	printf("%d”N%dŒ%d“ú‚Ì%s—j“ú‚Å‚·\n", y, m, d, week);

	return 0;
}

