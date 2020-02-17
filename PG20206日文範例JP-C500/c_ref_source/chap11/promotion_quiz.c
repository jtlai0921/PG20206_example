/* promotion_quiz.c */
#include <stdio.h>

int main(void)
{
	long l = -1;
	unsigned int n = 1;

	if (l > n)
		printf("l(%lu) > n(%lu)\n");
	else
		printf("l(%lu) <= n(%lu)\n");

	return 0;
}

