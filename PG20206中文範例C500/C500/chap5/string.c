#include <stdio.h>

int main(void)
{
	char r[] = {'A', 'B', 'C'};   /* 雖然不會造成編譯錯誤，但非正確寫法 */
	char s[] = {'A', 'B', 'C', '\0'};
	char t[] = "ABC";
/*	char *v = {'A', 'B', 'C'};   */ /* 錯誤寫法 */
	char *u = "ABC";

	printf("%s\n", r);
	printf("%s\n", s);
	printf("%s\n", t);
	printf("%s\n", u);

	return 0;
}

