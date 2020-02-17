/*
 * list5.c 
 *
 */
#include <stdio.h>

union foo {
	int val;
	char b[4];
};

int main(void)
{
	union foo bar;

	bar.b[0] = 0x12;
	bar.b[1] = 0x34;
	bar.b[2] = 0x56;
	bar.b[4] = 0x78;

	printf("共用体のサイズ %d\n", sizeof(bar));
	printf("val = %x\n", bar.val);

	return 0;
}

