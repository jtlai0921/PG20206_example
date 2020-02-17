#include <stdio.h>

int main(void)
{
	char *s[] = {
		"梅雨が明けました",
		"蒸し暑い日々が続いています",
		"でも、会社のマシンルームはとてつもなく寒いです",
		"風邪を引かないよう気を付けましょう",
		NULL
	};
	char **p;

	p = s;
	//p = &s[0];   // この書き方でもOK
	
	while (*p) {
		printf("%s\n", *p++);
	}

	return 0;
}

