#include <stdio.h>

int main(void)
{
	char buf[32];

	printf("•¶Žš—ñ‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
	while (fgets(buf, sizeof(buf), stdin) != NULL) {
		printf("%s", buf);
		printf("•¶Žš—ñ‚ð“ü—Í‚µ‚Ä‚­‚¾‚³‚¢: ");
	}

	return 0;
}

