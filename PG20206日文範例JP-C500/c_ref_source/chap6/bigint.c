/*
 * BCD���Z
 */
#include <stdio.h>

#define LEN 20      /* �ő包�� */

void sub(int len, char *num1, char *num2)
{
	char ans[LEN + 1];  /* ���Z���� */
	int i, sum, carry, n1, n2;

	carry = 0;   /* �J��グ */
	for (i = len - 1; i >= 0; i--) {  /* ���ʂ���1���������Z���Ă��� */
		n1 = num1[i] - '0';
		n2 = num2[i] - '0';

		sum = n1 + n2 + carry;
		if (sum >= 10) {   /* �J��グ���� */
			sum -= 10;
			carry = 1;
		} else {
			carry = 0;
		}

		ans[i] = (char)(sum + '0');
	}
	ans[len] = '\0';  

	/* ���Z���Ɣ���Z���̕\�� */
	printf("  %s\n", num1);
	printf("+ %s\n", num2);

	printf(" ");

	/* �ŏ�ʌ��ŌJ��グ���������Ă�����C"1"���o�͂��� */
	if (carry)
		printf("1");
	else
		printf(" ");

	printf("%s\n\n", ans);
}

int main(void)
{
	sub(3, "123", "456");
	sub(9, "123456789", "987654321");
	sub(13, "9000000121212", "8080808080808");

	return 0;
}

