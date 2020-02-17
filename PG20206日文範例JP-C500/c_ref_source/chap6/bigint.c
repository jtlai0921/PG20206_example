/*
 * BCD‰‰Z
 */
#include <stdio.h>

#define LEN 20      /* Å‘åŒ…” */

void sub(int len, char *num1, char *num2)
{
	char ans[LEN + 1];  /* ‰ÁZŒ‹‰Ê */
	int i, sum, carry, n1, n2;

	carry = 0;   /* ŒJ‚èã‚° */
	for (i = len - 1; i >= 0; i--) {  /* ‰ºˆÊ‚©‚ç1Œ…‚¸‚Â‘«‚µZ‚µ‚Ä‚¢‚­ */
		n1 = num1[i] - '0';
		n2 = num2[i] - '0';

		sum = n1 + n2 + carry;
		if (sum >= 10) {   /* ŒJ‚èã‚°”­¶ */
			sum -= 10;
			carry = 1;
		} else {
			carry = 0;
		}

		ans[i] = (char)(sum + '0');
	}
	ans[len] = '\0';  

	/* ‰ÁZ”‚Æ”í‰ÁZ”‚Ì•\¦ */
	printf("  %s\n", num1);
	printf("+ %s\n", num2);

	printf(" ");

	/* ÅãˆÊŒ…‚ÅŒJ‚èã‚°‚ª”­¶‚µ‚Ä‚¢‚½‚çC"1"‚ğo—Í‚·‚é */
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

