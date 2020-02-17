#include <stdio.h>
#include <time.h>

int main(void)
{
	time_t t;
	struct tm *val;
	char *week[] = {
		"sun",
		"mon",
		"tue",
		"wed",
		"thu",
		"fri",
		"sat",
	};

	t = time(NULL);
	val = localtime(&t);
	if (val != NULL) {
		printf("%d/%d/%d %d:%d:%d (%s)\n",
				val->tm_year + 1900,
				val->tm_mon + 1,
				val->tm_mday,
				val->tm_hour,
				val->tm_min,
				val->tm_sec,
				week[val->tm_wday]);
	}

	return 0;
}

