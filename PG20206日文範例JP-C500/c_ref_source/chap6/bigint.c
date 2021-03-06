/*
 * BCD演算
 */
#include <stdio.h>

#define LEN 20      /* 最大桁数 */

void sub(int len, char *num1, char *num2)
{
	char ans[LEN + 1];  /* 加算結果 */
	int i, sum, carry, n1, n2;

	carry = 0;   /* 繰り上げ */
	for (i = len - 1; i >= 0; i--) {  /* 下位から1桁ずつ足し算していく */
		n1 = num1[i] - '0';
		n2 = num2[i] - '0';

		sum = n1 + n2 + carry;
		if (sum >= 10) {   /* 繰り上げ発生 */
			sum -= 10;
			carry = 1;
		} else {
			carry = 0;
		}

		ans[i] = (char)(sum + '0');
	}
	ans[len] = '\0';  

	/* 加算数と被加算数の表示 */
	printf("  %s\n", num1);
	printf("+ %s\n", num2);

	printf(" ");

	/* 最上位桁で繰り上げが発生していたら，"1"を出力する */
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

