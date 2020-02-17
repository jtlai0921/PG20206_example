/*
 * C�����^�C�����C�u�������g���ă}���`�X���b�h����������
 *
 * for compile:
 *  >cl /MT thread_console.c 
 */
#include <windows.h>
#include <process.h>
#include <stdio.h>

int count = 0;

// �X���b�h�֐�
unsigned __stdcall do_handler(void *arg)
{
	int val = *(int *)arg;

	count += val;
	Sleep(3000);

	return 0;
}

// ���C���֐�
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
		printf("�X���b�h�������ł��܂���ł���\n");

	} else {
		// �X���b�h�̗D��x��ݒ肷��
		if (SetThreadPriority(hd, THREAD_PRIORITY_LOWEST) == 0) {
			printf("�D��x�̐ݒ�Ɏ��s���܂���\n");
		}

		WaitForSingleObject(hd, INFINITE);
		CloseHandle(hd); // �X���b�h�n���h�������
	}

	if (p_hd != NULL) {
		CloseHandle(p_hd);
	}

	printf("count=%d", count);

	return 0;
}

