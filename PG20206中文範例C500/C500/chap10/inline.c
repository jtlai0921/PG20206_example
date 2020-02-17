/*
 * inline.c
 *
 */
#include <stdio.h>

#ifdef TEST
#define INLINE inline
#else
#define INLINE 
#endif

INLINE void do_heavy(int num)
{
	int i, val;
	char dummy[8000];

	for (i = 0 ; i < 65535 ; i++) {
		val = num << 2 + 17 * num + num * num;
	}
}

void sub(void)
{
	do_heavy(10);
	do_heavy(1000);
	do_heavy(1000000);

}

int main(void)
{
	sub();

	return 0;
}


