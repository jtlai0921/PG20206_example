/* 
 * 求出平方根
 *
 */
#include <stdio.h>

double my_sqrt(double num)
{
	double x, x0;

	x0 = num;
	for (;;) {
		x = (x0 + num/x0) / 2;
		if (x >= x0)
			break;
		x0 = x;
	} 

	return (x0);
}

int main(void)
{
	int n;
	double ret;

	for (n = 1 ; n < 10 ; n++) {
		ret = my_sqrt(n);
		printf("√%d = %.15f\n", n, ret);
	}

	return 0;
}

