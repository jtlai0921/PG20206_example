#include <stdio.h>

int main(void)
{
	int n, val;
	char *str = "moemoe";

	n = 20030906;
	printf("%d\n", n);      /* 10�i�� */
	printf("%x\n", n);      /* 16�i�� */
	printf("%X\n", n);      /* 16�i���i�啶���j*/
	printf("%o\n", n);      /* 8�i�� */
	printf("%p\n", &n);     /* �|�C���^ */
	printf("%x\n", &n);     /* �|�C���^��%x�� */

	n = 123;
	printf("%5d�ł�\n", n);     /* 5���ŕ\�� */
	printf("%-5d�ł�\n", n);    /* 5���ŕ\�� */

	n = 0;
	printf("%c%n\n", n, &val);  /* �󕶎���\�� */
	printf("val %d\n", val);    /* �o�̓o�C�g�� */

	printf("%s\n", str);     /* �����񃊃e���� */
	printf("%.3s\n", str);   /* 3����������\������ */
	printf("%.*s\n", 4, str);   /* 4����������\������ */
	printf("%3c\n", str[0]); /* 3���ŕ�����\�� */

	printf("%%%%%%%s\n", str);   /* %���g�̕\�� */

	return 0;
}

