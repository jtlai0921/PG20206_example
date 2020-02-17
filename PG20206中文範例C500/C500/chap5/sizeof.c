/*
 * sizeof.c
 */
#include <stdio.h>
#include <string.h>

void sub(char *s)
{
	printf("sub: %d %d\n", strlen(s), sizeof(s));
}

int main(void)
{
	char s[] = "Security\0Administrator";
	char *t = "Security\0Administrator";

	printf("%d %d\n", strlen(s), sizeof(s));
	sub(s);

	printf("%d %d\n", strlen(t), sizeof(t));
	sub(t);

	return 0;
}

