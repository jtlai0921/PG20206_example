#include <stdio.h>

int main(void)
{
	int n, val;
	char buf[1024];
	char c;

	printf("数値を入力してください:");
	scanf("%d", &n);
	printf("n = %d\n", n);

	printf("文字を入力してください:");
	scanf("%c", &c);
	printf("c = %c\n", c);

	printf("文字列を入力してください:");
	scanf("%s", buf);
	printf("buf = %s\n", buf);

	printf("数値を入力してください:");
	scanf("%d", &val);
	printf("val = %d\n", val);

	return 0;
}

