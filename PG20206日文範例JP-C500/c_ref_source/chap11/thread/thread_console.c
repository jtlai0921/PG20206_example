/*
 * Cランタイムライブラリを使ってマルチスレッドを実現する
 *
 * for compile:
 *  >cl /MT thread_console.c 
 */
#include <windows.h>
#include <process.h>
#include <stdio.h>

int count = 0;

// スレッド関数
unsigned __stdcall do_handler(void *arg)
{
	int val = *(int *)arg;

	count += val;
	Sleep(3000);

	return 0;
}

// メイン関数
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
		printf("スレッドが生成できませんでした\n");

	} else {
		// スレッドの優先度を設定する
		if (SetThreadPriority(hd, THREAD_PRIORITY_LOWEST) == 0) {
			printf("優先度の設定に失敗しました\n");
		}

		WaitForSingleObject(hd, INFINITE);
		CloseHandle(hd); // スレッドハンドルを閉じる
	}

	if (p_hd != NULL) {
		CloseHandle(p_hd);
	}

	printf("count=%d", count);

	return 0;
}

