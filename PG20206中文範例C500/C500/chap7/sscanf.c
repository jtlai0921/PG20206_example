#include <stdio.h>

int main(void)
{
	char buf[128], week[16];
	int y, m, d;

	printf("今天是幾年幾月幾日星期幾?(YYYY/MM/HH 星期)");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d/%d/%d %15s", &y, &m, &d, week);
//	sscanf(buf, "%d/%d/%d %s", &y, &m, &d, week);

	printf("今天是%d年%d月%d日星期%s\n", y, m, d, week);

	return 0;
}

