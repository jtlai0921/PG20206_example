/*
 * list4a.c 
 *
 */
#include <stdio.h>

int x = 10;
extern int y;  /* externは実はなくても動く */

int main(void)
{
	extern int z;

	printf("x=%d y=%d z=%d\n", x, y, z);

	return 0;
}

