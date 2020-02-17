/*
 * Win32 APIを使ってマルチスレッドを実現する
 *
 * for compile:
 *  >cl thread_win32.c user32.lib kernel32.lib
 */
#include <windows.h>

int count = 0;

// スレッド関数
void do_handler(DWORD val)
{
	count += val;
	Sleep(3000);
}

// メイン関数
int WINAPI WinMain(
  HINSTANCE hInstance,      // 現在のインスタンスのハンドル
  HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
  LPSTR lpCmdLine,          // コマンドライン
  int nCmdShow              // 表示状態
) 
{
	HANDLE hd;
	DWORD tid;
	int val = 333;
	char buf[256];

	hd = CreateThread(
			NULL, 
			0,
			(LPTHREAD_START_ROUTINE)do_handler,
			(LPVOID)val,
			0,
			&tid
			);


	if (hd == NULL) {
		MessageBox(NULL, "スレッドが生成できませんでした", "エラー", 
			MB_OK | MB_ICONEXCLAMATION);

	} else {
		WaitForSingleObject(hd, INFINITE);
	}

	sprintf(buf, "count=%d", count);
	MessageBox(NULL, buf, "結果", MB_OK);

	return 0;
}

