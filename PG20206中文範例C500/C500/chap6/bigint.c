/*
 * BCD�B��
 */
#include <stdio.h>

#define LEN 20      /* �̤j��� */

void sub(int len, char *num1, char *num2)
{
	char ans[LEN + 1];  /* �[�k���G */
	int i, sum, carry, n1, n2;

	carry = 0;   /* �i�� */
	for (i = len - 1; i >= 0; i--) {  /* �q�U������Ƴv�찵�[�k */
		n1 = num1[i] - '0';
		n2 = num2[i] - '0';

		sum = n1 + n2 + carry;
		if (sum >= 10) {   /* �o�Ͷi�� */
			sum -= 10;
			carry = 1;
		} else {
			carry = 0;
		}

		ans[i] = (char)(sum + '0');
	}
	ans[len] = '\0';  

	/* �[�ƻP�Q�[�ƪ���� */
	printf("  %s\n", num1);
	printf("+ %s\n", num2);

	printf(" ");

	/* �p�G�̤W������Ƶo�Ͷi��A�h��X"1" */
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

