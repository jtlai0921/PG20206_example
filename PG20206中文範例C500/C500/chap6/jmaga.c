/* 2003/3/17
 *
 * [問題]
 * 填滿下列數學式中的空白部分。
 * 可使用1到9的數字，但是各數字只能各使用1次。
 * 也就是說，這些空格中剛好會各使用到一次1~9的數字。
 * 另外，其解一共有幾種呢？
 *
 * □□+□□□+□□□□=3717
 *
 * [解答例]
 * 97 + 158 + 3462 = 3717
 *
 * Presented by YUTAKA
 */

#include <stdio.h>

#define BIT(n) (1 << (n))
#define SOLVE_NUMBER 3717

int anscnt = 0;
int sum2, sum3;

void make_digit(int max_digit, int n, int sum, int flag)
{
	int i;

	if (n >= max_digit) {
		int val;

		if (max_digit == 2) {
			sum2 = sum;
			make_digit(3, 0, 0, flag);
		}
		if (max_digit == 3) {
			val = sum2 + sum;
			if (val > SOLVE_NUMBER)
				return;
			sum3 = sum;
			make_digit(4, 0, 0, flag);
		}
		if (max_digit == 4) {
			val = sum2 + sum3 + sum;
			if (val == SOLVE_NUMBER) {
				printf("%d + %d + %d = %d\n", sum2, sum3, sum, SOLVE_NUMBER);
				anscnt++;
			}
		}

		return;
	}

	for (i = 1 ; i <= 9 ; i++) {
		if (flag & BIT(i))
			continue;

		make_digit(max_digit, n + 1, 10*sum + i, flag | BIT(i));

	}
}

int main(void)
{
	make_digit(2, 0, 0, 0);

	printf("一共有 %d 種解\n", anscnt);

	return 0;
}


