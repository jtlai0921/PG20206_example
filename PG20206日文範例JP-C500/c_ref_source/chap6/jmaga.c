/* 2003/3/17
 *
 * jmaga.c - 「Jマガ用コンピュータパズル」
 *
 * [問題]
 * 次の数式を満たすように空欄を数字で埋めよ。
 * ただし、数字は1から9までが使用でき、かつ各数字が使用できる
 * のは一回のみとする。つまり、空欄には1から9までの数字が格納
 * されることになる。また、解は何とおりあるだろうか。
 *
 *   □□＋□□□＋□□□□＝3717
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

	printf("解 %d とおり\n", anscnt);

	return 0;
}


