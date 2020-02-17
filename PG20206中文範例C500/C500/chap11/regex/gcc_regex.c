/*
 * gcc_regex.c - �u�bC�y�����ϥΥ��W��{�v
 *   with gcc
 *
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>


/*
 * �q���~�X���o���~�T������ܥX��
 */
void show_error(regex_t *preg, int code)
{
	char tmp[BUFSIZ];

	regerror(code, preg, tmp, sizeof(tmp));
	printf("%s (%d)\n", tmp, code);
}


/*
 * �ϥΥ��W��{(buf)�ӹ�¤�r���e(target)���j�M
 */
void do_regex(char *target, char *buf)
{
	regex_t reg;
	regmatch_t match[10];
	char tmp[BUFSIZ];
	int i, ret, cnt, len;

	/* �sĶ���W��{
	 * REG_NEWLINE�O�b.*�����]�t���檺���w�覡(��Perl)�C
	 */
	ret = regcomp(&reg, buf, REG_NEWLINE | REG_EXTENDED);
	if (ret) {
		printf("�sĶ����. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	cnt = sizeof(match) / sizeof(match[0]);
	/*
	 * �j�M�r��target
	 */
	ret = regexec(&reg, target, cnt, match, 0);
	if (ret) {
		printf("��異��. %d\n", ret);
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
	 * ����sĶ�������W��{���w�İ�
	 */
	regfree(&reg);
}

int main(void)
{
	/* ��r���e */
	char target[] = "Hello, Linux world. This program is made by GNU rx Library.";

	/* ���W��{ */
	char *regbuf[] = {
		"(Lin(ux))",
		"[Ll]inux",
		"(Linux(.*d)\\.)",
		"yutaka",
		"*hogehoge",
		0
	};
	char **p = regbuf;

	printf("��r���e %s\n", target);

	while (*p) {
		printf("\n=== ���W��{ %s:\n", *p);
		do_regex(target, *p);
		p++;
	}

	return 0;
}

