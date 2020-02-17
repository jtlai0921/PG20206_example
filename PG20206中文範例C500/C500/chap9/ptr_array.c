#include <stdio.h>

int main(void)
{
	char *s[] = {
		"梅雨季結束了",
		"現在每天持續著溼熱的天氣",
		"不過，公司的電腦房非常非常冷",
		"小心千萬不要感冒了",
		NULL
	};
	char **p;

	p = s;
	//p = &s[0];   //也可以寫成這樣
	
	while (*p) {
		printf("%s\n", *p++);
	}

	return 0;
}

