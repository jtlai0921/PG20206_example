#include <stdio.h>
#include <string.h>

int data[32];
int bar[32];

int main(void)
{
	int i;
	
	for (i = 0 ; i < 32 ; i++) {
		data[i] = i;
	}

	//memcpy(bar, data, 32);   // �o�˥u�|�ƻs32�Ӧ줸��
	memcpy(bar, data, sizeof(data));

	for (i = 0 ; i < 32 ; i++) {
		printf("%d ", bar[i]);
	}

	return 0;
}

