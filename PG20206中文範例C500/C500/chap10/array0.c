/*
 * array0.c
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct packet {
	int size;
	int data[0];       // array of length zero (gcc extension)
} packet_t;

int main(void)
{
	packet_t *ptr;
	int size, i;

	size = 256;
	ptr = malloc(sizeof(packet_t) + size*sizeof(int));
	if (ptr != NULL) {
		ptr->size = size;
		for (i = 0 ; i < size ; i++) {
			ptr->data[i] = i;
		}

		for (i = 0 ; i < ptr->size ; i++) {
			printf("%d ", ptr->data[i]);
		}
		printf("\n");

		free(ptr);
	}

	return 0;
}

