#include <stdio.h>
#include <string.h>

int data[32];
int bar[32];

int main(void)
{
	int i;
	
	for (i = 0 ; i < 32 ; i++) {
		data[i] = i;
	}

	//memcpy(bar, data, 32);   // これは32バイトしかコピーしない
	memcpy(bar, data, sizeof(data));

	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", bar[i]);
	}

	return 0;
}

