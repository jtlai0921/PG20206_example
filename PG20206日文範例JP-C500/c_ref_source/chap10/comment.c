//
// comment.c - 「gcc拡張機能 C++風コメント」
//
#include <stdio.h>

// main関数
int main(void)
{
	int a, b, c;

	a = 10; b = 5;
	c = a//*comment*/b;
	;

	printf("gcc//software %d\n", c);

	return 0;
}

