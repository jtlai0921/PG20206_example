/*
 * list4a.c 
 *
 */
#include <stdio.h>

int x = 10;
extern int y;  /* 沒有extern其實還是可以執行 */

int main(void)
{
	extern int z;

	printf("x=%d y=%d z=%d\n", x, y, z);

	return 0;
}

