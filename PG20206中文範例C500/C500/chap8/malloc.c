#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define NBPG 4096   /* 4KB */

int main(void)
{
	char *ptr, *mp;
	size_t size;

	size = 128;
	mp = malloc(size + NBPG);
	if (mp == NULL) {
		printf("Not memory!\n");
		exit(1);
	}
	/* 使mp落在NBPG位元組位址 */
	ptr = (char *)(((intptr_t)mp + (NBPG - 1)) & ~(NBPG - 1));

	printf("mp = %p  ptr = %p\n", mp, ptr);

	free(mp);

	return 0;
}


