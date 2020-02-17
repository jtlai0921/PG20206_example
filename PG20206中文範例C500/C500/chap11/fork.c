/*
 * fork.c
 *
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

char buf[BUFSIZ];

int main(void)
{
	pid_t pid;
	int status, i;

	strcpy(buf, "main");

	pid = fork();
	if (pid == 0) {  /* child process */
		strcpy(buf, "child");
		printf("%s\n", buf);
		exit(1);
	}

	strcpy(buf, "parent");
	wait(&status);
	printf("%s\n", buf);

	return 0;
}

