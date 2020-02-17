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
	while (t == time(NULL))  /* •bj‚ð0‚É‚·‚é */
		;

	base = 0;
	t = time(NULL);
	while (t == time(NULL))  /* 1•bŠÔ‚ÌƒJƒEƒ“ƒg”‚ð‹‚ß‚é */
		base++;
	//printf("base-count %ld\n", base);

	sub();

	rest = 0;
	t2 = time(NULL);
	while (t2 == time(NULL))  /* ’[”ŽžŠÔ‚ÌƒJƒEƒ“ƒg */
		rest++;

	sec = t2 - t - 1;
	mili = 100 - 100*rest/base;

	printf("ŽÀsŽžŠÔ %ld.%ld •b\n", sec, mili);

	return 0;
}


