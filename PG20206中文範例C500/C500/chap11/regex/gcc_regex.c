/*
 * gcc_regex.c - 「在C語言中使用正規表現」
 *   with gcc
 *
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>


/*
 * 從錯誤碼取得錯誤訊息並顯示出來
 */
void show_error(regex_t *preg, int code)
{
	char tmp[BUFSIZ];

	regerror(code, preg, tmp, sizeof(tmp));
	printf("%s (%d)\n", tmp, code);
}


/*
 * 使用正規表現(buf)來對純文字內容(target)做搜尋
 */
void do_regex(char *target, char *buf)
{
	regex_t reg;
	regmatch_t match[10];
	char tmp[BUFSIZ];
	int i, ret, cnt, len;

	/* 編譯正規表現
	 * REG_NEWLINE是在.*中不包含換行的指定方式(似Perl)。
	 */
	ret = regcomp(&reg, buf, REG_NEWLINE | REG_EXTENDED);
	if (ret) {
		printf("編譯失敗. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	cnt = sizeof(match) / sizeof(match[0]);
	/*
	 * 搜尋字串target
	 */
	ret = regexec(&reg, target, cnt, match, 0);
	if (ret) {
		printf("比對失敗. %d\n", ret);
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
	 * 釋放編譯完的正規表現的緩衝區
	 */
	regfree(&reg);
}

int main(void)
{
	/* 文字內容 */
	char target[] = "Hello, Linux world. This program is made by GNU rx Library.";

	/* 正規表現 */
	char *regbuf[] = {
		"(Lin(ux))",
		"[Ll]inux",
		"(Linux(.*d)\\.)",
		"yutaka",
		"*hogehoge",
		0
	};
	char **p = regbuf;

	printf("文字內容 %s\n", target);

	while (*p) {
		printf("\n=== 正規表現 %s:\n", *p);
		do_regex(target, *p);
		p++;
	}

	return 0;
}

