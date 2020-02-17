#include <stdio.h>
#include <process.h>

int main(void)
{
	int ret;

	ret = execlp("notepad", "notepad", "system.c", NULL);
	printf("ret %d\n", ret);

	return 0;
}

