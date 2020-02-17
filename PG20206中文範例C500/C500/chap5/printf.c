#include <stdio.h>

int main(void)
{
	char *str = "task rates 5%. \12800 yen \n";
//	char *str = "task rates 5%. \\12800 yen \n";

	printf("%s", str);

	return 0;
}

