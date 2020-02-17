#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

void sub3(void)
{
	printf("sub3()\n");
}

void sub2(void)
{
	longjmp(env, 1);
	printf("sub2()\n");
}

void sub(void)
{
	printf("sub()\n");
}

int main(void)
{

	/* ŠO•”‚ÌŠÖ”‚©‚çƒWƒƒƒ“ƒv‚µ‚Ä‚«‚½ */
	if (setjmp(env)) {
		printf("setjmp() called!!\n");
		exit(1);
	}

	sub();
	sub2();
	sub3();

	return 0;
}

