/*
 * strcmp.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *input = "yes";

	if (strcmp(input, "yes") == 0) {
		printf("了解!\n");
	} else {
		printf("撤下~\n");
	}

	if (input == "yes") {   // 這個是NG
		printf("了解!\n");
	} else {
		printf("撤下~\n");
	}

	return 0;
}

