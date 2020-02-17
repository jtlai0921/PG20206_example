#include <stdio.h>

int main(void)
{
	char *str = "fusianasan";

	printf("%c\n", str[5]);
	printf("%c\n", 5[str]);

	printf("%c\n", "gikoneko"[3]);
	printf("%c\n", 3["gikoneko"]);

	return 0;
}

