#include <stdio.h>

int main(void)
{
	char r[] = {'A', 'B', 'C'};   /* �G���[�ɂ͂Ȃ�Ȃ����ԈႢ */
	char s[] = {'A', 'B', 'C', '\0'};
	char t[] = "ABC";
/*	char *v = {'A', 'B', 'C'};   */ /* ����̓G���[ */
	char *u = "ABC";

	printf("%s\n", r);
	printf("%s\n", s);
	printf("%s\n", t);
	printf("%s\n", u);

	return 0;
}

