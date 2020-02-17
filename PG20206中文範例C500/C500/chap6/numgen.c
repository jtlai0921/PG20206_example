/*
 * 產生獨一無二的數值
 */
#include <stdio.h>

int main(void)
{
	int i, j, k, num;
	int flag[4];

	flag[0] = 0;
	flag[1] = 0;
	flag[2] = 0;
	flag[3] = 0;

	/* 製作出1到3的數字所構成的數值 */
	for (i = 1 ; i <= 3 ; i++) {
		flag[i] = 1;

		for (j = 1 ; j <= 3 ; j++) {
			if (flag[j])
				continue;
			flag[j] = 1;

			for (k = 1 ; k <= 3 ; k++) {
				if (flag[k])
					continue;
				//flag[k] = 1;

				num = 100*i + 10*j + k;
				printf("%d\n", num);

				//flag[k] = 0;
			}

			flag[j] = 0;
		}

		flag[i] = 0;
	}

	return 0;
}

