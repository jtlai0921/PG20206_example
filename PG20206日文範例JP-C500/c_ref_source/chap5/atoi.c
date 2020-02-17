/*
 * atoi.c
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int n;
	long l;
	long long ll;

	if (argc == 1) {
		exit(1);
	}

	printf("argument = %s\n", argv[1]);

	n = atoi(argv[1]);
	l = atol(argv[1]);

	printf("n=%d\n", n);
	printf("l=%ld\n", l);

#ifdef __GNUC__
	ll = atoll(argv[1]);
	printf("ll=%lld\n", ll);
#else
	ll = _atoi64(argv[1]);
	printf("ll=%I64d\n", ll);
#endif

	return 0;
}

