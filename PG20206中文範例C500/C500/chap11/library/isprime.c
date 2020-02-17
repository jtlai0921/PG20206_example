/*
 * isprime.c
 */

int isprime(int num)
{
	int n;

	if (num < 2 || num % 2 == 0)  // even number
		return 0;

	for (n = 3 ; n * n <= num ; n += 2) {
		if (num % n == 0)
			return 0;
	}

	return 1;  // odd number
}

