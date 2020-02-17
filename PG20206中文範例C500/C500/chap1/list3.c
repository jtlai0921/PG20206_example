/* list3 */
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	char **p = envp;

	while (*p) {
		printf("%s\n", *p++);
	}

	return 0;
}

