/*
 * 使用C run-time函式庫來達成多執行緒
 *
 * for compile:
 *  >cl /MT thread_console.c 
 */
#include <windows.h>
#include <process.h>
#include <stdio.h>

int count = 0;

// 執行緒函數
unsigned __stdcall do_handler(void *arg)
{
	int val = *(int *)arg;

	count += val;
	Sleep(3000);

	return 0;
}

// main函數
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
		printf("執行緒產生失敗\n");

	} else {
		// 設定執行緒的優先權
		if (SetThreadPriority(hd, THREAD_PRIORITY_LOWEST) == 0) {
			printf("優先權設定失敗\n");
		}

		WaitForSingleObject(hd, INFINITE);
		CloseHandle(hd); // 關閉執行緒標示元
	}

	if (p_hd != NULL) {
		CloseHandle(p_hd);
	}

	printf("count=%d", count);

	return 0;
}

