#include <stdio.h>

void couting_sort(int len, int *data)
{
    static int count[10];
	int i, j;

    for (i = 0 ; i < len ; i++) {
        count[data[i]]++;
    }
    j = 0;
    for (i = 0 ; i < 10 ; i++) {
        if (count[i] > 0) {
            data[j++] = i;
        }
    }
}

int main(void)
{
    int data[] = {5, 1, 7, 3, 0, 2};
	int i;

    for (i = 0 ; i < 6 ; i++) 
        printf("%d ", data[i]); 
    printf("\n");

	couting_sort(6, data);
    
    for (i = 0 ; i < 6 ; i++) 
        printf("%d ", data[i]); 
    printf("\n");

    return 0;
}


