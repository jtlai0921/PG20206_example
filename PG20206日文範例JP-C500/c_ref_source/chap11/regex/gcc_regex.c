/*
 * gcc_regex.c - ��C���������ɽ����Ȥ���
 *   with gcc
 *
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>


/*
 * ���顼�����ɤ��饨�顼��å��������������ɽ�����롣
 */
void show_error(regex_t *preg, int code)
{
	char tmp[BUFSIZ];

	regerror(code, preg, tmp, sizeof(tmp));
	printf("%s (%d)\n", tmp, code);
}


/*
 * ����ɽ��(buf)�ˤ��ƥ�����ʸ��(target)�θ�����Ԥ���
 */
void do_regex(char *target, char *buf)
{
	regex_t reg;
	regmatch_t match[10];
	char tmp[BUFSIZ];
	int i, ret, cnt, len;

	/* ����ɽ���򥳥�ѥ��뤹�롣
	 * REG_NEWLINE�� .* �ʤɤ˲��Ԥ�ޤ�ʤ�����(Perl�饤��)��
	 */
	ret = regcomp(&reg, buf, REG_NEWLINE | REG_EXTENDED);
	if (ret) {
		printf("����ѥ���˼��Ԥ��ޤ���. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	cnt = sizeof(match) / sizeof(match[0]);
	/*
	 * ʸ���� target �򸡺�����
	 */
	ret = regexec(&reg, target, cnt, match, 0);
	if (ret) {
		printf("�ޥå��󥰤˼��Ԥ��ޤ���. %d\n", ret);
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
	 * ����ѥ��뤷������ɽ���ΥХåե����������
	 */
	regfree(&reg);
}

int main(void)
{
	/* �ƥ����� */
	char target[] = "Hello, Linux world. This program is made by GNU rx Library.";

	/* ����ɽ�� */
	char *regbuf[] = {
		"(Lin(ux))",
		"[Ll]inux",
		"(Linux(.*d)\\.)",
		"yutaka",
		"*hogehoge",
		0
	};
	char **p = regbuf;

	printf("�ƥ����� %s\n", target);

	while (*p) {
		printf("\n=== ����ɽ�� %s:\n", *p);
		do_regex(target, *p);
		p++;
	}

	return 0;
}

