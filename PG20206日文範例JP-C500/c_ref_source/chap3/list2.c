#include <stdio.h>

#define FOO 1
#define LINUX_VERSION_CODE 0x020417

int main()
{

#ifdef FOO
        printf("foo\n");
#else
        printf("foo2\n");
#endif

#ifndef BAR
        printf("bar\n");
#endif

#if (LINUX_CODE_VERSION < 0x020400)
        printf("zot\n");
#endif

        printf("%x\n", LINUX_VERSION_CODE);

        return 0;
}

