#include <stdio.h>

int main(void)
{
	int n, val;
	char *str = "moemoe";

	n = 20030906;
	printf("%d\n", n);      /* 10�i�� */
	printf("%x\n", n);      /* 16�i�� */
	printf("%X\n", n);      /* 16�i��i�啶?�j*/
	printf("%o\n", n);      /* 8�i�� */
	printf("%p\n", &n);     /* ���� */
	printf("%x\n", &n);     /* ��%x�Ӫ�ܫ��� */

	n = 123;
	printf("%5d�ł�\n", n);     /* ��5��ƨӪ�� */
	printf("%-5d�ł�\n", n);    /* ��5��ƨӪ�� */

	n = 0;
	printf("%c%n\n", n, &val);  /* ���null */
	printf("val %d\n", val);    /* ��X�줸�� */

	printf("%s\n", str);     /* �r��`�� */
	printf("%.3s\n", str);   /* �u���3�Ӧr */
	printf("%.*s\n", 4, str);   /* �u���4�Ӧr */
	printf("%3c\n", str[0]); /* ��3��ƨ���ܦr�� */

	printf("%%%%%%%s\n", str);   /* ���%���� */

	return 0;
}

