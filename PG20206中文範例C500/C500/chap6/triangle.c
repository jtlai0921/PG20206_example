/* 
 * 三角形的面積
 *
 */
#include <stdio.h>
#include <math.h>

void area(double a, double b, double c)
{
	double s, S;

	s = (a + b + c) / 2;
	S = s*(s-a)*(s-b)*(s-c);
	S = sqrt(S);

	printf("三角形(%f,%f,%f)的面積是 %f\n", a, b, c, S);
}

int main(void)
{
	area(3, 4, 5);
	area(11, 12, 13);

	return 0;
}

