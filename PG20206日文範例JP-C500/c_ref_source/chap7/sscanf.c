#include <stdio.h>

int main(void)
{
	char buf[128], week[16];
	int y, m, d;

	printf("今日の日付と曜日は(YYYY/MM/HH 曜日)？");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d/%d/%d %15s", &y, &m, &d, week);
//	sscanf(buf, "%d/%d/%d %s", &y, &m, &d, week);

	printf("%d年%d月%d日の%s曜日です\n", y, m, d, week);

	return 0;
}

