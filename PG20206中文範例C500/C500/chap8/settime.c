/*
 * settime.c - �u�]�w�t�ήɶ��v ���ϥήɽФp��
 *
 * for compile:
 *  >cl /nologo /W3 settime.c kernel32.lib 
 *
 */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	SYSTEMTIME time;

	memset(&time, 0, sizeof(time));
	time.wYear = 2003;
	time.wMonth = 9;
	time.wDayOfWeek = 0;
	time.wDay = 14;

	if (SetLocalTime(&time)) {
		printf("�]�w���\\n");
	} else {
		printf("�]�w���� (%d)\n", GetLastError());
	}

	return 0;
}


