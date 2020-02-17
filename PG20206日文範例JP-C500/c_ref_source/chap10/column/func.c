#include <stdio.h>

void getResourceParameter(void)
{
	printf("%s\n", __func__);
}

void sub(void)
{
	printf("%s\n", __func__);
}

int main(void)
{
	printf("%s\n", __func__);

	sub();
	getResourceParameter();

	return 0;
}

