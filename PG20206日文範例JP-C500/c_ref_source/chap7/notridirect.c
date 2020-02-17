/*
 * リダイレクトされない標準I/Oを作る
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

int main(void)
{
	int con, tmp;

	tmp = dup(1);
#ifdef _WIN32
	con = open("CON", O_WRONLY);
#else
	con = open("/dev/pts/0", O_WRONLY);
#endif
	if (con == 0) exit(1);
	dup2(con, 1);
	printf("foo\n");
	dup2(tmp, 1);
	printf("bar\n");
	close(con);

	return 0;
}

