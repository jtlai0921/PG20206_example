#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <locale.h>
#include <wchar.h>

int main(void)
{
	wchar_t c = L'¶À';
	char mbs[MB_LEN_MAX];
	int s;
	int i;

	_wsetlocale(LC_ALL, L".950");

	s = wctomb(mbs, c);
	printf("%.*s\n", s, mbs);

	for (i = 0 ; i < s ; i++) {
		printf("%x ", (unsigned char)mbs[i]);
	}
	printf("\n");


	return 0;
}

