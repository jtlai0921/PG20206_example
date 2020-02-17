/*
 * esqrt.c - �u�u�ϥξ�ƹB��ӨD�o����ڡv
 *
 */
#include <stdio.h>

int integer_sqrt(int num)
{
	int k, sum;

	if (num < 0)
		return (-1);   /* �Y�O�t�ƫh�o�Ϳ��~ */

	if (num == 0)
		return (0);   /* ��0 = 0 */

	/* �ϥΩ_�ƦC�`�X���S�ʡA�ӨD�X�����
	 * 1 + 3 + 5 + �K�K  + (2k - 1) = k^2
	 * ��k��1�����
	 */
	sum = 0;
	for (k = 1 ; ; k++) {
		sum += (2*k - 1);

		if (sum > num)
			return (-1);   /* ����ڤ������ */

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

