/*
 * regexw.c - �uC����Ő��K�\�����g���v
 *   with Borland C++Compiler 5.5.1 
 *
 */
#include <stdio.h>
#include <string.h>
#include <pcreposix.h>


/*
 * �G���[�R�[�h����G���[���b�Z�[�W���擾���ĕ\������B
 */
void show_error(regex_t *preg, int code)
{
	char tmp[BUFSIZ];

	regerror(code, preg, tmp, sizeof(tmp));
	printf("%s (%d)\n", tmp, code);
}


/*
 * ���K�\��(buf)�ɂ��e�L�X�g����(target)�̌������s���B
 */
void do_regex(char *target, char *buf)
{
	regex_t reg;
	regmatch_t match[10];
	char tmp[BUFSIZ];
	int i, ret, cnt, len;

	/* ���K�\�����R���p�C������B
	 * REG_NEWLINE�� .* �Ȃǂɉ��s���܂߂Ȃ��w��(Perl���C�N)�B
	 */
	ret = regcomp(&reg, buf, REG_NEWLINE);
	if (ret) {
		printf("�R���p�C���Ɏ��s���܂���. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	cnt = sizeof(match) / sizeof(match[0]);
	/*
	 * ������ target ����������
	 */
	ret = regexec(&reg, target, cnt, match, 0);
	if (ret) {
		printf("�}�b�`���O�Ɏ��s���܂���. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	for (i = 0 ; i < cnt ; i++) {
		if (match[i].rm_so == -1 || match[i].rm_eo == -1)
			break;

		len = match[i].rm_eo - match[i].rm_so;

		strncpy(tmp, &target[match[i].rm_so], len);
		tmp[len] = 0;

		printf("[%d] %s\n", i, tmp);
	}

	/*
	 * �R���p�C���������K�\���̃o�b�t�@���������
	 */
	regfree(&reg);
}

int main(void)
{
	/* �e�L�X�g */
	char target[] = "Hello, Linux world. This program is made by GNU rx Library.";

	/* ���K�\�� */
	char *regbuf[] = {
		"(Lin(ux))",
		"[Ll]inux",
		"(Linux(.*d)\\.)",
		"yutaka",
		"*hogehoge",
		0
	};
	char **p = regbuf;

	printf("�e�L�X�g %s\n", target);

	while (*p) {
		printf("\n=== ���K�\�� %s:\n", *p);
		do_regex(target, *p);
		p++;
	}

	return 0;
}


