#include <stdio.h>

int main(void)
{
	int n, val;
	char *str = "moemoe";

	n = 20030906;
	printf("%d\n", n);      /* 10進位 */
	printf("%x\n", n);      /* 16進位 */
	printf("%X\n", n);      /* 16進位�i����?�j*/
	printf("%o\n", n);      /* 8進位 */
	printf("%p\n", &n);     /* 指標 */
	printf("%x\n", &n);     /* 用%x來表示指標 */

	n = 123;
	printf("%5d���愧n", n);     /* 用5位數來表示 */
	printf("%-5d���愧n", n);    /* 用5位數來表示 */

	n = 0;
	printf("%c%n\n", n, &val);  /* 顯示null */
	printf("val %d\n", val);    /* 輸出位元數 */

	printf("%s\n", str);     /* 字串常數 */
	printf("%.3s\n", str);   /* 只顯示3個字 */
	printf("%.*s\n", 4, str);   /* 只顯示4個字 */
	printf("%3c\n", str[0]); /* 用3位數來顯示字元 */

	printf("%%%%%%%s\n", str);   /* 顯示%本身 */

	return 0;
}

