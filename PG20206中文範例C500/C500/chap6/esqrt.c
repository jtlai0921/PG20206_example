/*
 * esqrt.c - ㄏノ俱计笲衡ㄓ―眔キよ
 *
 */
#include <stdio.h>

int integer_sqrt(int num)
{
	int k, sum;

	if (num < 0)
		return (-1);   /* 璝琌璽计玥祇ネ岿粇 */

	if (num == 0)
		return (0);   /* ≡0 = 0 */

	/* ㄏノ计羆疭┦ㄓ―キよ
	 * 1 + 3 + 5 +   + (2k - 1) = k^2
	 * “k≠1俱计
	 */
	sum = 0;
	for (k = 1 ; ; k++) {
		sum += (2*k - 1);

		if (sum > num)
			return (-1);   /* キよぃ俱计 */

		if (sum == num)
			break;
	}

	return (k);
}

int main(void)
{
	int x, val;

	for (x = 0 ; x <= 100 ; x++) {
		val = integer_sqrt(x);
		if (val != -1)
			printf("≡%d =  %d\n", x, val);
	}

	return 0;
}

