/* 2003/3/17
 *
 * [���D]
 * �񺡤U�C�ƾǦ������ťճ����C
 * �i�ϥ�1��9���Ʀr�A���O�U�Ʀr�u��U�ϥ�1���C
 * �]�N�O���A�o�ǪŮ椤��n�|�U�ϥΨ�@��1~9���Ʀr�C
 * �t�~�A��Ѥ@�@���X�ةO�H
 *
 * ����+������+��������=3717
 *
 * [�ѵ���]
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

	printf("�@�@�� %d �ظ�\n", anscnt);

	return 0;
}


