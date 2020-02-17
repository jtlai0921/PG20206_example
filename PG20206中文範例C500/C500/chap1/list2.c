/* list2 */
#include <stdio.h>

int main(int argc, char **argv)
{
	int i;

	printf("引入的數量 %d\n", argc);

	for (i = 0 ; i < argc ; i++) {
		printf("%s\n", argv[i]);
	}

	return 0;
}

