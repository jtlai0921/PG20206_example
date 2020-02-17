#include <stdio.h>
#include <stdlib.h>

#define NUM 5

typedef struct {
	int count;
	int data[1];
} resource_t;

int main(void)
{
	resource_t *ptr;
	int i;

	ptr = malloc(sizeof(resource_t) + sizeof(int) * (NUM - 1));
	if (ptr == NULL)
		exit(1);

	ptr->count = NUM;
	for (i = 0 ; i < ptr->count ; i++) {
		ptr->data[i] = 'C' + i;
	}

	for (i = 0 ; i < ptr->count ; i++) {
		printf("%c\n", ptr->data[i]);
	}
	free(ptr);

	return 0;
}

