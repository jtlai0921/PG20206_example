/* int64.c */
#include <stdio.h>

int main(void)
{
	long long int num = 9223372036854775807LL;
	int i;

	num = 1;
	for (i = 0 ; i < 63 ; i++) {
		num *= 2;
		printf("num = %Ld\n", num);
	}

	return 0;
}

