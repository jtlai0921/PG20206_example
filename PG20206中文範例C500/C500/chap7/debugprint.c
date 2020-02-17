#include <stdio.h>

#ifdef DEBUG
#define DBGPRINT printf
#else
#define DBGPRINT (void)
#endif


int main(void)
{
	int i;

	for (i = 0 ; i < 10 ; i++) {
		DBGPRINT("%d\n", i);
	}
	printf("i = %d\n", i);

	return 0;
}

