#include <stdio.h>

int main(void)
{
	char buf[256];
	int c, n;

	n = 0;
	while ((c = getchar()) != EOF) {
		if (n >= 255)
			break;
		buf[n++] = c;
	}
	buf[n] = '\0';

	printf("%s\n", buf);

	return 0;
}

