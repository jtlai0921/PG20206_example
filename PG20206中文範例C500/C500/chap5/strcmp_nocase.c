/*
 * strcmp_nocase.c
 */
#include <stdio.h>

#ifdef _WIN32
#	include <string.h>
#	define CMP(s1, s2) _stricmp(s1, s2)
#else
#	include <strings.h>
#	define CMP(s1, s2) strcasecmp(s1, s2)
#endif

int main(void)
{
	char *input = "Yes";

	if (CMP(input, "yes") == 0) {
		printf("���G���@�P\n");
	} else {
		printf("���G�����@�P\n");
	}

	return 0;
}

