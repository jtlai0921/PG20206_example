#include <stdio.h>
#include <time.h>

void sub(void)
{
	int i, j;

	for (i = 0 ; i < 100000 ; i++)
		for (j = 0 ; j < 100000 ; j++)
			;
}

int main(void)
{
	time_t t, t2, base, rest;
	long sec, mili;

	t = time(NULL);
	while (t == time(NULL))  /* 秒針を0にする */
		;

	base = 0;
	t = time(NULL);
	while (t == time(NULL))  /* 1秒間のカウント数を求める */
		base++;
	//printf("base-count %ld\n", base);

	sub();

	rest = 0;
	t2 = time(NULL);
	while (t2 == time(NULL))  /* 端数時間のカウント */
		rest++;

	sec = t2 - t - 1;
	mili = 100 - 100*rest/base;

	printf("実行時間 %ld.%ld 秒\n", sec, mili);

	return 0;
}


