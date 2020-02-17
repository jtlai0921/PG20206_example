/* 
 * sieve.c - �u�D�X��ơv(sieve of Eratosthnenes)
 *
 */
#include <stdio.h>

#define PRIME_MAX 100
int primetable[PRIME_MAX];

void sieve(void)
{
	int i, p;

	/* �N�x�}�Ҧ��n���]��1 */
	for (i = 0 ; i < PRIME_MAX ; i++) {
		primetable[i] = 1;
	}
	primetable[0] = primetable[1] = 0;

	for (i = 2 ; i < PRIME_MAX ; i++) {
		if (primetable[i] == 1) {
			/* �Y�O���ƫh�N��z�� */
			for (p = i*2 ; p < PRIME_MAX ; p += i) {
				primetable[p] = 0;
			}
		}
	}

	/* �ѤU���N�O��� */
	for (i = 0 ; i < PRIME_MAX ; i++) {
		if (primetable[i] == 1) {
			printf("%d ", i);
		}
	}
	printf("\n");
}

int main(void)
{
	sieve();

	return 0;
}

