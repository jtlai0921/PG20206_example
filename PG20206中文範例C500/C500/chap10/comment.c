//
// comment.c - 「gcc擴充功能 C++風格註解」
//
#include <stdio.h>

// main函數
int main(void)
{
	int a, b, c;

	a = 10; b = 5;
	c = a//*comment*/b;
	;

	printf("gcc//software %d\n", c);

	return 0;
}

