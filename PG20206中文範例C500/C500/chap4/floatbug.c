#include <stdio.h>

int main(void)
{
	float a;
	int i;

	a = 0;
	for (i = 0 ; i < 10 ; i++) {
		a += 0.1;
	}

	printf("%f\n", a);

	if (a == 1.0f) 
		printf("�۵�\n");
	else
		printf("���۵�\n");

	return 0;
}

