#include <stdio.h>

int main(void)
{
	float a;
	int i;

	a = 0;
	for (i = 0 ; i < 10 ; i++) {
		a += 0.1;
	}

	printf("%.20f\n", a);

	if (a == 1.0f) 
		printf("“™‚µ‚¢\n");
	else
		printf("“™‚µ‚­‚È‚¢\n");

	return 0;
}

