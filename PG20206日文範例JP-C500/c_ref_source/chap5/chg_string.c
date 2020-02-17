#include <stdio.h>

int main(void)
{
	char s[] = "yutaka";

	printf("%s\n", s);
	s[0] = 'Y';
	//s[0] = "Y";   /* エラーにはならないが間違い */
	//s = "hirata";	  /* エラー！ */
	printf("%s\n", s);

	return 0;
}

