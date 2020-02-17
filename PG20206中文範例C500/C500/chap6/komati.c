/*
 * 使用位元運算來產生小町數
 */
#include <stdio.h>

#define BIT(n) (1 << (n-1))

void sub(int n, int bit, int number)
{
	int i;

	if (n >= 9) {
		printf("%d\n", number);
		return;
	}

	for (i = 1 ; i <= 9 ; i++) {
		/* 檢查是否已使用過 */
		if (bit & BIT(i))
			continue;

		sub(n + 1, bit | BIT(i), number*10 + i);
	}
}

int main(void)
{
	sub(0, 0, 0);

	return 0;
}

