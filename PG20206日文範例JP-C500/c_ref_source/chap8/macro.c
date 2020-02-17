#include <stdio.h>

int main(void)
{
	printf("BUFSIZ %d\n", BUFSIZ);
	printf("EOF %d\n", EOF);
	printf("NULL %c\n", NULL);

	printf("%s %d\n", __FILE__, __LINE__);
	printf("%s %s\n", __DATE__, __TIME__);
	printf("%s\n", __TIMESTAMP__);

	return 0;
}


