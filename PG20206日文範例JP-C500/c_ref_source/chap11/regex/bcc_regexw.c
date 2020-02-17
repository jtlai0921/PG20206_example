/*
 * regexw.c - 「C言語で正規表現を使う」
 *   with Borland C++Compiler 5.5.1 
 *
 */
#include <stdio.h>
#include <string.h>
#include <pcreposix.h>


/*
 * エラーコードからエラーメッセージを取得して表示する。
 */
void show_error(regex_t *preg, int code)
{
	char tmp[BUFSIZ];

	regerror(code, preg, tmp, sizeof(tmp));
	printf("%s (%d)\n", tmp, code);
}


/*
 * 正規表現(buf)によるテキスト文書(target)の検索を行う。
 */
void do_regex(char *target, char *buf)
{
	regex_t reg;
	regmatch_t match[10];
	char tmp[BUFSIZ];
	int i, ret, cnt, len;

	/* 正規表現をコンパイルする。
	 * REG_NEWLINEは .* などに改行を含めない指定(Perlライク)。
	 */
	ret = regcomp(&reg, buf, REG_NEWLINE);
	if (ret) {
		printf("コンパイルに失敗しました. %d\n", ret);
		show_error(&reg, ret);
		return;
	}

	cnt = sizeof(match) / sizeof(match[0]);
	/*
	 * 文字列 target を検索する
	 */
	ret = regexec(&reg, target, cnt, match, 0);
	if (ret) {
		printf("マッチングに失敗しました. %d\n", ret);
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
	 * コンパイルした正規表現のバッファを解放する
	 */
	regfree(&reg);
}

int main(void)
{
	/* テキスト */
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

	printf("テキスト %s\n", target);

	while (*p) {
		printf("\n=== 正規表現 %s:\n", *p);
		do_regex(target, *p);
		p++;
	}

	return 0;
}


