#include <stdio.h>

int main(void)
{
	char buf[128], week[16];
	int y, m, d;

	printf("���ѬO�X�~�X��X��P���X?(YYYY/MM/HH �P��)");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d/%d/%d %15s", &y, &m, &d, week);
//	sscanf(buf, "%d/%d/%d %s", &y, &m, &d, week);

	printf("���ѬO%d�~%d��%d��P��%s\n", y, m, d, week);

	return 0;
}

