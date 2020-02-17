/*
 * fifo.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	ssize_t size;
	char buf[BUFSIZ], *msg;

	fd = open("fifo", O_RDONLY | O_NONBLOCK);
	if (fd == -1) {
		perror("Can't open FIFO");
		exit(1);
	}

	msg = "hello, Linux world!\n"; 

	if (fork() == 0) {  /* child process */
		fd = open("fifo", O_WRONLY | O_NONBLOCK);
		if (fd == -1) {
			perror("Can't open FIFO(2)");
			exit(1);
		}
		size = write(fd, msg, strlen(msg));
		printf("wrote bytes %d\n", size);
		close(fd);
		exit(1);
	}
	size = read(fd, buf, BUFSIZ);
	printf(">%*s\n", size, buf);

	wait(NULL);

	close(fd);

	return 0;
}

