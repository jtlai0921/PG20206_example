#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

char map[SIZE][SIZE] = {
	{'a', 'b', 'c'},
	{'d', 'e', 'f'},
	{'g', 'h', 'i'},
};


void display(char ptr[SIZE][SIZE])
{
	int x, y;

	for (y = 0 ; y < SIZE ; y++) {
		for (x = 0 ; x < SIZE ; x++) {
			printf("%c", ptr[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(void)
{
	display(map);

	return 0;
}


