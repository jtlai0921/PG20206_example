/*
 * strcmp.c
 */
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *input = "yes";

	if (strcmp(input, "yes") == 0) {
		printf("�����I\n");
	} else {
		printf("�P���`\n");
	}

	if (input == "yes") {   // �����NG
		printf("�����I\n");
	} else {
		printf("�P���`\n");
	}

	return 0;
}

