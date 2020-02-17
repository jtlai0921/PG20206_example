/*
 * esqrt.c - �u�������Z�݂̂ŕ����������߂�v
 *
 */
#include <stdio.h>

int integer_sqrt(int num)
{
	int k, sum;

	if (num < 0)
		return (-1);   /* �����̓G���[�Ƃ��� */

	if (num == 0)
		return (0);   /* ��0 = 0 */

	/* ���̘a�̊֌W���g���āC�����������߂�B
	 * 1 + 3 + 5 + �c�c + (2k - 1) = k^2
	 * ��k��1�̐���
	 */
	sum = 0;
	for (k = 1 ; ; k++) {
		sum += (2*k - 1);

		if (sum > num)
			return (-1);   /* �������͐����ɂȂ�Ȃ� */

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
			printf("��%d =  %d\n", x, val);
	}

	return 0;
}

