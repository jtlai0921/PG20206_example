#include <stdio.h>

int main(void)
{
	int n, val;
	char buf[1024];
	char c;

	printf("請輸入數值:");
	scanf("%d", &n);
	printf("n = %d\n", n);

	//rewind(stdin);
	fflush(stdin);
	printf("請輸入字元:");
	scanf("%c", &c);
	printf("c = %c\n", c);

	printf("請輸入字串:");
	scanf("%s", buf);
	printf("buf = %s\n", buf);

	printf("請輸入數值:");
	scanf("%d", &val);
	printf("val = %d\n", val);

	return 0;
}

