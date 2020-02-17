/*
 * �ϥ�C run-time�禡�w�ӹF���h�����
 *
 * for compile:
 *  >cl /MT thread_console.c 
 */
#include <windows.h>
#include <process.h>
#include <stdio.h>

int count = 0;

// ��������
unsigned __stdcall do_handler(void *arg)
{
	int val = *(int *)arg;

	count += val;
	Sleep(3000);

	return 0;
}

// main���
int main(void)
{
	HANDLE hd;
	unsigned tid;
	int val = 333;
	char buf[256];
	DWORD pid;
	HANDLE p_hd;

	pid = GetCurrentProcessId();
	p_hd = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
	if (p_hd != NULL) {
		SetPriorityClass(p_hd, IDLE_PRIORITY_CLASS);
	}

	hd = (HANDLE)_beginthreadex(
			NULL, 
			0, 
			do_handler,
			&val,
			0,
			&tid
			);

	if (hd == 0) {
		printf("��������ͥ���\n");

	} else {
		// �]�w��������u���v
		if (SetThreadPriority(hd, THREAD_PRIORITY_LOWEST) == 0) {
			printf("�u���v�]�w����\n");
		}

		WaitForSingleObject(hd, INFINITE);
		CloseHandle(hd); // ����������Хܤ�
	}

	if (p_hd != NULL) {
		CloseHandle(p_hd);
	}

	printf("count=%d", count);

	return 0;
}

