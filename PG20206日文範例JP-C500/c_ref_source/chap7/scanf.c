#include <stdio.h>

int main(void)
{
	int n, val;
	char buf[1024];
	char c;

	printf("”’l‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
	scanf("%d", &n);
	printf("n = %d\n", n);

	printf("•¶š‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
	scanf("%c", &c);
	printf("c = %c\n", c);

	printf("•¶š—ñ‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
	scanf("%s", buf);
	printf("buf = %s\n", buf);

	printf("”’l‚ğ“ü—Í‚µ‚Ä‚­‚¾‚³‚¢:");
	scanf("%d", &val);
	printf("val = %d\n", val);

	return 0;
}

