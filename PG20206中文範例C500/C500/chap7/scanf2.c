#include <stdio.h>

int main(void)
{
	int n, val;
	char buf[1024];
	char c;

	printf("�п�J�ƭ�:");
	scanf("%d", &n);
	printf("n = %d\n", n);

	//rewind(stdin);
	fflush(stdin);
	printf("�п�J�r��:");
	scanf("%c", &c);
	printf("c = %c\n", c);

	printf("�п�J�r��:");
	scanf("%s", buf);
	printf("buf = %s\n", buf);

	printf("�п�J�ƭ�:");
	scanf("%d", &val);
	printf("val = %d\n", val);

	return 0;
}

