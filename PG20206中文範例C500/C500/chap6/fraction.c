/*
 * 分數的加法
 */
#include <stdio.h>

typedef struct {
	int numerator;   /* 分子 */
	int denominator; /* 分母 */
} fract_t;

int gcd(int x, int y)
{
	int t;

	while (y != 0) {
		t = x % y;
		x = y;
		y = t;
	}
	return (x);
}

int lcd(int x, int y)
{
	int n;

	n = x*y / gcd(x,y);
	return (n);
}

void sub(int len, fract_t *n)
{
	int i, val, deno, num;
	double ans;

	if (len < 2)
		return;

	/* 求出分母的最小公倍數 */
	val = lcd(n[0].denominator, n[1].denominator);
	for (i = 2 ; i < len ; i++) {
		val = lcd(n[i].denominator, val);
	}
	deno = val;
	//printf("lcd %d\n", deno);

	num = 0;
	for (i = 0 ; i < len ; i++) {
		num += (deno / n[i].denominator * n[i].numerator);
	}

	ans = (double)num / deno;

	printf("分子/分母 = %d/%d = %.10f\n", num, deno, ans);
}

void sub_float(int len, fract_t *num)
{
	int i;
	double val;

	val = 0;
	for (i = 0 ; i < len ; i++) {
		val += (double)num[i].numerator / num[i].denominator;
	}

	printf("%.10f\n", val);
}

int main(void)
{
	fract_t n[4] = {
		{1,2},
		{1,3},
		{1,4},
		{1,5},
	};

	sub(4, n);
	sub_float(4, n);

	return 0;
}


