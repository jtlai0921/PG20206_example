#include <stdio.h>

struct parent {
	int a;
	struct child {
		char *b;
		int c[5];
		struct grandchild {
			long *d[3];
		} *uu;
	} u;
};

int main(void)
{
	struct parent data, *ptr;
	char *cval;
	int val, *addr;
	long *lval;
	struct grandchild foo;

	ptr = &data;
	val = data.a;
	val = ptr->a;

	cval = data.u.b;
	cval = ptr->u.b;

	addr = &data.u.c[0];
	addr = &ptr->u.c[0];

	data.u.uu = &foo;
	lval = data.u.uu->d[0];
	lval = ptr->u.uu->d[0];

	return 0;
}

