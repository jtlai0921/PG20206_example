/* list1 */
#include <stdio.h>

int main(void)
{
	int val[] = {1, 2, 3};
	const int *p;      
	int * const p2 = val; 
	const int * const p3 = val; 

	p = val;
	p++;
	//*p = 5;  
	printf("%d %d %d\n", val[0], val[1], val[2]);

	//p2 = val;
	//p2++;
	*p2 = 7;
	printf("%d %d %d\n", val[0], val[1], val[2]);

	//p3 = val;
	//p3++;
	//*p3 = 9;
	printf("%d %d %d\n", val[0], val[1], val[2]);

	return 0;
}

