#include <stdio.h>

int main(void)
{
	char *s[] = {
		"���B�u�����F",
		"�{�b�C�ѫ���۷ü����Ѯ�",
		"���L�A���q���q���ЫD�`�D�`�N",
		"�p�ߤd�U���n�P�_�F",
		NULL
	};
	char **p;

	p = s;
	//p = &s[0];   //�]�i�H�g���o��
	
	while (*p) {
		printf("%s\n", *p++);
	}

	return 0;
}

