#include <stdio.h>

int main(void)
{
	char buf[128], week[16];
	int y, m, d;

	printf("�����̓��t�Ɨj����(YYYY/MM/HH �j��)�H");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d/%d/%d %15s", &y, &m, &d, week);
//	sscanf(buf, "%d/%d/%d %s", &y, &m, &d, week);

	printf("%d�N%d��%d����%s�j���ł�\n", y, m, d, week);

	return 0;
}

