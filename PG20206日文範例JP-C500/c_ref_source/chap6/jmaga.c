/* 2003/3/17
 *
 * jmaga.c - �uJ�}�K�p�R���s���[�^�p�Y���v
 *
 * [���]
 * ���̐����𖞂����悤�ɋ󗓂𐔎��Ŗ��߂�B
 * �������A������1����9�܂ł��g�p�ł��A���e�������g�p�ł���
 * �͈̂��݂̂Ƃ���B�܂�A�󗓂ɂ�1����9�܂ł̐������i�[
 * ����邱�ƂɂȂ�B�܂��A���͉��Ƃ��肠�邾�낤���B
 *
 *   �����{�������{����������3717
 *
 * [�𓚗�]
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

	printf("�� %d �Ƃ���\n", anscnt);

	return 0;
}


