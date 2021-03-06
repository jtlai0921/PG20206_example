/*
 * settime_linux.c - 「設定系統時間」 ★請小心使用
 *
 * for compile:
 *  # gcc settime_linux.c
 *
 */
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	struct tm time;
	time_t t;
	struct timeval val;

	memset(&time, 0, sizeof(time));
	time.tm_year = 2003 - 1900;
	time.tm_mon = 9 - 1;
	time.tm_wday = 0;
	time.tm_mday = 14;

	t = timelocal(&time);
	memset(&val, 0, sizeof(val));
	val.tv_sec = t;

	if (settimeofday(&val, NULL) == 0) {
		printf("設定成功\n");
	} else {
		perror("設定失敗\n");
	}

	return 0;
}

