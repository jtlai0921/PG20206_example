#include <stdio.h>

int main(void)
{
	int n, val;
	char buf[1024];
	char c;

	printf("���l����͂��Ă�������:");
	scanf("%d", &n);
	printf("n = %d\n", n);

	printf("��������͂��Ă�������:");
	scanf("%c", &c);
	printf("c = %c\n", c);

	printf("���������͂��Ă�������:");
	scanf("%s", buf);
	printf("buf = %s\n", buf);

	printf("���l����͂��Ă�������:");
	scanf("%d", &val);
	printf("val = %d\n", val);

	return 0;
}

