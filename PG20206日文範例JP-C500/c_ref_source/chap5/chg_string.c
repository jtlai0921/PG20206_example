#include <stdio.h>

int main(void)
{
	char s[] = "yutaka";

	printf("%s\n", s);
	s[0] = 'Y';
	//s[0] = "Y";   /* �G���[�ɂ͂Ȃ�Ȃ����ԈႢ */
	//s = "hirata";	  /* �G���[�I */
	printf("%s\n", s);

	return 0;
}

