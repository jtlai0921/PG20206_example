/* 
 * list4.c - 「クラッシュダンププログラム」
 */
#include <stdio.h>
#include <stdlib.h>

char *ptr;

void sub(int size)
{
	int i;

	ptr = malloc(sizeof(char) * size);
	for (i = 0 ; i < size ; i++) {
		ptr[i] = i;
	}
	free(ptr);
}

int main(void)
{
	int i;

	for (i = 256 ;  ; i *= 2) {
		printf("size %d\n", i);
		sub(i);
		*ptr = 0;
	}

	return 0;
}

