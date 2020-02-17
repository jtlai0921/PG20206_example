#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	printf("argc %d\n", argc);

	if (argc == 1) {
		exit(1);
	}

	return 0;
}

