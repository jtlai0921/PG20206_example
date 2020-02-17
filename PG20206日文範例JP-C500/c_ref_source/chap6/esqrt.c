/*
 * esqrt.c - 「整数演算のみで平方根を求める」
 *
 */
#include <stdio.h>

int integer_sqrt(int num)
{
	int k, sum;

	if (num < 0)
		return (-1);   /* 負数はエラーとする */

	if (num == 0)
		return (0);   /* √0 = 0 */

	/* 奇数列の和の関係を使って，平方根を求める。
	 * 1 + 3 + 5 + …… + (2k - 1) = k^2
	 * ※k≧1の整数
	 */
	sum = 0;
	for (k = 1 ; ; k++) {
		sum += (2*k - 1);

		if (sum > num)
			return (-1);   /* 平方根は整数にならない */

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
			printf("√%d =  %d\n", x, val);
	}

	return 0;
}

