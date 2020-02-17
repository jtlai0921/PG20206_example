#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int main(void)
{
	if (_setmode(fileno(stdout), _O_BINARY) == -1) {
		printf("setmode error!\n");
	}

	printf("bar\n");

	return 0;
}

