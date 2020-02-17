#include <stdio.h>

int main(void)
{
	char org[128];
	char *p = &org[16];
	int i;

	for (i = -16 ; i <= 16 ; i++) {
		p[i] = i;
	}
	for (i = 0 ; i <= 32 ; i++) {
		printf("%d ", org[i]);
	}

	return 0;
}

