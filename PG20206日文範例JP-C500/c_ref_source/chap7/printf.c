#include <stdio.h>

int main(void)
{
	int n, val;
	char *str = "moemoe";

	n = 20030906;
	printf("%d\n", n);      /* 10進数 */
	printf("%x\n", n);      /* 16進数 */
	printf("%X\n", n);      /* 16進数（大文字）*/
	printf("%o\n", n);      /* 8進数 */
	printf("%p\n", &n);     /* ポインタ */
	printf("%x\n", &n);     /* ポインタを%xで */

	n = 123;
	printf("%5dです\n", n);     /* 5桁で表示 */
	printf("%-5dです\n", n);    /* 5桁で表示 */

	n = 0;
	printf("%c%n\n", n, &val);  /* 空文字を表示 */
	printf("val %d\n", val);    /* 出力バイト数 */

	printf("%s\n", str);     /* 文字列リテラル */
	printf("%.3s\n", str);   /* 3文字だけを表示する */
	printf("%.*s\n", 4, str);   /* 4文字だけを表示する */
	printf("%3c\n", str[0]); /* 3桁で文字を表示 */

	printf("%%%%%%%s\n", str);   /* %自身の表示 */

	return 0;
}

