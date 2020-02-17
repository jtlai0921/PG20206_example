/* 
 * sieve.c - 「素数を求める」エラトステネスのふるい
 *
 */
#include <stdio.h>

#define PRIME_MAX 100
int primetable[PRIME_MAX];

void sieve(void)
{
	int i, p;

	/* テーブルに'1'をセットする */
	for (i = 0 ; i < PRIME_MAX ; i++) {
		primetable[i] = 1;
	}
	primetable[0] = primetable[1] = 0;

	for (i = 2 ; i < PRIME_MAX ; i++) {
		if (primetable[i] == 1) {
			/* 倍数たちはふるいから落とす */
			for (p = i*2 ; p < PRIME_MAX ; p += i) {
				primetable[p] = 0;
			}
		}
	}

	/* 残ったものが素数となる */
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

