/*
 * hexfloat.c
 *
 */
#include <stdio.h>

int main(void)
{
	float f[5] = {
		0x1.fp0,   // 1 15/16
		0x0.1p0,   // 1/16
		0x0.11p0,  // 1/16 + 1/256
		0x11.11p0, // 17 + 1/16 + 1/256
		0x3.1p5    // (3+1/16)x2^5
	};
	int i;

	for (i = 0 ; i < 5 ; i++) {
		printf("%f\n", f[i]);
	}

	return 0;
}

