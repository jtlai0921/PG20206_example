#include <stdio.h>

int main(void)
{
	char s[] = "yutaka";

	printf("%s\n", s);
	s[0] = 'Y';
	//s[0] = "Y";   /* ���|�o�Ϳ��~�A���D���T�g�k */
	//s = "hirata";	  /* ���~! */
	printf("%s\n", s);

	return 0;
}

