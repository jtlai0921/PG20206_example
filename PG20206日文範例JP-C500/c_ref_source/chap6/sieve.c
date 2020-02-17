/* 
 * sieve.c - �u�f�������߂�v�G���g�X�e�l�X�̂ӂ邢
 *
 */
#include <stdio.h>

#define PRIME_MAX 100
int primetable[PRIME_MAX];

void sieve(void)
{
	int i, p;

	/* �e�[�u����'1'���Z�b�g���� */
	for (i = 0 ; i < PRIME_MAX ; i++) {
		primetable[i] = 1;
	}
	primetable[0] = primetable[1] = 0;

	for (i = 2 ; i < PRIME_MAX ; i++) {
		if (primetable[i] == 1) {
			/* �{�������͂ӂ邢���痎�Ƃ� */
			for (p = i*2 ; p < PRIME_MAX ; p += i) {
				primetable[p] = 0;
			}
		}
	}

	/* �c�������̂��f���ƂȂ� */
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

