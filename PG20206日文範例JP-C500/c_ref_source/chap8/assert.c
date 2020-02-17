#include <stdio.h>
#include <assert.h>

int data[128];

int main(void)
{
	int i;

	for (i = 0 ; i < 256 ; i++) {
		assert(i < 128);
		data[i] = i;
	}

	return 0;
}

