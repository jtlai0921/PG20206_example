#include <stdio.h>

int main(void)
{
	char s[] = "yutaka";

	printf("%s\n", s);
	s[0] = 'Y';
	//s[0] = "Y";   /* 不會發生錯誤，但非正確寫法 */
	//s = "hirata";	  /* 錯誤! */
	printf("%s\n", s);

	return 0;
}

