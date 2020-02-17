/*
 * arraysize.c
 */
#include <stdio.h>
#include <string.h>

#define ELEM(n) (sizeof(n) / sizeof(n[0]))

int main(void)
{
	int a[256];
	char b[512];
	char *c = "Yuna Rikku Paine";

	printf("%d\n", ELEM(a));
	printf("%d\n", ELEM(b));
	printf("%d\n", ELEM(c));

	return 0;
}

