/*
 * 九去法
 */
#include <stdio.h>
#include <string.h>

void is_multiple_of_nine(char *buf)
{
	int i, sum;
	char *p;

	p = buf;
	sum = 0;
	while (*p) {
		sum += (*p - '0');
		p++;
	}

	if (sum > 0 && sum % 9 == 0) {
		//printf("各位數的總合 %d\n", sum);
		printf("%s 是9的倍數\n", buf);
	}
}

int main(void)
{
	int i;

	is_multiple_of_nine("81");
	is_multiple_of_nine("123456789");
	is_multiple_of_nine("1234567890");
	is_multiple_of_nine("800000000000000001");
	is_multiple_of_nine("900000000000000001");

	return 0;
}

