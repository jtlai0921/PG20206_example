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
		printf("������\n");
	else
		printf("�������Ȃ�\n");

	return 0;
}

