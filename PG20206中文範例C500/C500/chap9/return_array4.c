#include <stdio.h>
#include <stdlib.h>

int *sub(void)
{
	int *arr;
	int i;

	arr = malloc(sizeof(int) * 32);
	if (arr == NULL) 
		exit(1);

	for (i = 0 ; i < 32 ; i++) {
		arr[i] = i;
	}

	return (arr);
}

int main(void)
{
	int *ptr, i;

	ptr = sub();
	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", ptr[i]);
	}
	printf("\n");

	free(ptr);  /* 用完後要記得釋放 */

	return 0;
}

