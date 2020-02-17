#include <stdio.h>

int main(void)
{
	char r[] = {'A', 'B', 'C'};   /* エラーにはならないが間違い */
	char s[] = {'A', 'B', 'C', '\0'};
	char t[] = "ABC";
/*	char *v = {'A', 'B', 'C'};   */ /* これはエラー */
	char *u = "ABC";

	printf("%s\n", r);
	printf("%s\n", s);
	printf("%s\n", t);
	printf("%s\n", u);

	return 0;
}

