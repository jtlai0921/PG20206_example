/*
 * case_ranges.c
 *
 */
#include <stdio.h>

void sub(int val)
{
	printf("val = %d\n", val);

	switch (val) {
	case 1:
		printf("val is '1' number\n");
		break;

	case 2 ... 10:
		printf("val is '2' - '10' number\n");
		break;

	default:
		printf("val is not '1' - '10' number\n");
		break;
	}
}

int main(void)
{
	sub(-1);
	sub(1);
	sub(5);
	sub(11);

	return 0;
}

