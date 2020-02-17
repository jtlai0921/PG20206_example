#include <stdio.h>

typedef struct array {
	int data[32];
} array_t;

int main(void)
{
	array_t foo, bar;
	int i;

	for (i = 0 ; i < 32 ; i++) {
		foo.data[i] = i;
	}

	/* ˆêŠ‡‚µ‚ÄƒRƒs[‚Å‚«‚é */
	bar = foo;

	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", bar.data[i]);
	}

	return 0;
}

