/* 
 * list6.c - 「ぶらさがりelse問題」
 *
 */
#include <stdio.h>

int main(void)
{
    int n = 10, m = 0;

    if (n > 5) 
        if (n > 10) 
            m = 1;
    else {
        m = 2;
    }

    printf("m %d\n", m);

    return 0;
}

