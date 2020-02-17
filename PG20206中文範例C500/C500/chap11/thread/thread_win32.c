/*
 * 使用Win32 API來實現多執行緒
 *
 * for compile:
 *  >cl thread_win32.c user32.lib kernel32.lib
 */
#include <windows.h>

int count = 0;

// 執行緒函數
void do_handler(DWORD val)
{
	count += val;
	Sleep(3000);
}

// main函數
int WINAPI WinMain(
  HINSTANCE hInstance,      //現在實體(instance)的標示元
  HINSTANCE hPrevInstance,  //以前實體(instance)的標示元
  LPSTR lpCmdLine,          //命令列
  int nCmdShow              //顯示狀態
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
		MessageBox(NULL, "執行緒產生失敗", "錯誤", 
			MB_OK | MB_ICONEXCLAMATION);

	} else {
		WaitForSingleObject(hd, INFINITE);
	}

	sprintf(buf, "count=%d", count);
	MessageBox(NULL, buf, "結果", MB_OK);

	return 0;
}

