/*
 * settime.c - �u�V�X�e���̎��Ԃ�ݒ肷��v ����舵������
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
		printf("�ݒ�ɐ������܂���\n");
	} else {
		printf("�ݒ�Ɏ��s���܂��� (%d)\n", GetLastError());
	}

	return 0;
}


