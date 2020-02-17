/*
 * offset.c - 「構造体のオフセット」
 */
#include <stdio.h>
#include <stddef.h>   

#undef offsetof
#define offsetof(type, mem) ((size_t)(&((type *)0)->mem))

struct offset {
    char a;
    char b;
    int c;
    char d;
    long e;
};

int main(void)
{
    struct offset tmp;
    struct offset *p = &tmp;

    printf("p %p\n", p);
    printf("a %p\n", &p->a);
    printf("b %p\n", &p->b);
    printf("c %p\n", &p->c);
    printf("d %p\n", &p->d);
    printf("e %p\n\n", &p->e);

    printf("a %d\n", offsetof(struct offset, a));
    printf("b %d\n", offsetof(struct offset, b));
    printf("c %d\n", offsetof(struct offset, c));
    printf("d %d\n", offsetof(struct offset, d));
    printf("e %d\n", offsetof(struct offset, e));

    return 0;
}

