/*
 * strcmp.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *input = "yes";

	if (strcmp(input, "yes") == 0) {
		printf("¹ðI\n");
	} else {
		printf("Pû`\n");
	}

	if (input == "yes") {   // ±êÍNG
		printf("¹ðI\n");
	} else {
		printf("Pû`\n");
	}

	return 0;
}

