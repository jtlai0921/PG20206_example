/*
 * リダイレクトされない標準入力を作る
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
	char buf[128];

	tmp = dup(0);  // 0=fileno(stdin) 
#ifdef _WIN32
	con = open("CON", O_RDONLY);
#else
	con = open("/dev/pts/0", O_RDONLY);
#endif
	if (con == 0) exit(1);
	dup2(con, 0);
	fgets(buf, sizeof(buf), stdin);
	printf("buf = %s", buf);
	dup2(tmp, 0);
	close(con);

	return 0;
}

