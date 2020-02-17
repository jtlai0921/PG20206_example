#include <stdio.h>
#include <stdlib.h>

void disp_binary(char num)
{
	int i, ret;

	for (i = sizeof(num) * 8 - 1 ; i >= 0 ; i--) {
		ret = num & (1 << i);
		printf("%d", ret ? 1 : 0);
	}
}

void disp_float(float n)
{
	char buf[4];
	int i;

	printf("%f =\n", n);

	/* バッファへコピー。リトルエンディアンになることに注意 */
	memcpy(buf, &n, sizeof(n));

	for (i = 3 ; i >= 0 ; i--) {
		disp_binary(buf[i]);
		printf(" ");
	}
	printf("\nSXXXXXXX XMMMMMMM MMMMMMMM MMMMMMMM\n");
}

void disp_double(double n)
{
	char buf[8];
	int i;

	printf("%f = \n", n);

	/* バッファへコピー。リトルエンディアンになることに注意 */
	memcpy(buf, &n, sizeof(n));

	for (i = 7 ; i >= 0 ; i--) {
		disp_binary(buf[i]);
		printf(" ");
	}
	printf("\nSXXXXXXX XXXXMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM MMMMMMMM\n");
}

int main(int argc, char **argv)
{
	float f;
	double d;

	if (argc == 1)
		exit(1);

	sscanf(argv[1], "%f", &f);
	disp_float(f);
	printf("\n");

	sscanf(argv[1], "%lf", &d);
	disp_double(d);

	return 0;
}

