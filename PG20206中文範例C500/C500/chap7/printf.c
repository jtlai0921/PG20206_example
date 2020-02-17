#include <stdio.h>

int main(void)
{
	int n, val;
	char *str = "moemoe";

	n = 20030906;
	printf("%d\n", n);      /* 10秈 */
	printf("%x\n", n);      /* 16秈 */
	printf("%X\n", n);      /* 16秈乮戝暥?乯*/
	printf("%o\n", n);      /* 8秈 */
	printf("%p\n", &n);     /* 夹 */
	printf("%x\n", &n);     /* ノ%xㄓボ夹 */

	n = 123;
	printf("%5d偱偡\n", n);     /* ノ5计ㄓボ */
	printf("%-5d偱偡\n", n);    /* ノ5计ㄓボ */

	n = 0;
	printf("%c%n\n", n, &val);  /* 陪ボnull */
	printf("val %d\n", val);    /* 块じ计 */

	printf("%s\n", str);     /* ﹃盽计 */
	printf("%.3s\n", str);   /* 陪ボ3 */
	printf("%.*s\n", 4, str);   /* 陪ボ4 */
	printf("%3c\n", str[0]); /* ノ3计ㄓ陪ボじ */

	printf("%%%%%%%s\n", str);   /* 陪ボ%セō */

	return 0;
}

