/*
 * strcmp.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *input = "yes";

	if (strcmp(input, "yes") == 0) {
		printf("�F��!\n");
	} else {
		printf("�M�U~\n");
	}

	if (input == "yes") {   // �o�ӬONG
		printf("�F��!\n");
	} else {
		printf("�M�U~\n");
	}

	return 0;
}

