/*
 * 使用多執行緒來執行高負荷的作業
 *
 * for compile:
 *  >cl thread_highload_job.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define MYWNDCLASS  "MYWNDCLASS"


typedef struct {
	int num;
	char ans[8129];
} ans_t;

HANDLE g_hd = NULL;


void busy_wait(void)
{
	int i, j;

	for (i = 0 ; i < 65535 ; i++) 
		for (j = 0 ; j < 65535 ; j++) 
			;
}

//
// 求出質因數分解
//
void do_factorize(ans_t *ans)
{
	char buf[8192], tmp[32]; // 緩衝區管理部分偷懶一下
	int n;
	int num;

	num = ans->num;

	sprintf(buf, "%d=", num);

	// 用2除到不能再除
	while (num >= 4) {
		if (num % 2)
			break;
		num /= 2;
		strcat(buf, "2�~");
	}

	// 用3以上的奇數去除
	n = 3;
	while (n * n <= num) {
		if (num % n)
			n += 2;  // 換下一個奇數

		num /= n;

		sprintf(tmp, "%d×", n);
		strcat(buf, tmp);
	}
	sprintf(tmp, "%d", num);
	strcat(buf, tmp);

	strcpy(ans->ans, buf);

	busy_wait();

	MessageBox(NULL, ans->ans, "計算結果", MB_OK);
}

// 視窗程序
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int val;
	ans_t ans;
	DWORD tid;

    switch (uMsg) {
	case WM_NCLBUTTONDBLCLK:
		MessageBox(NULL, "滑鼠點按了二下", "通知",
			MB_OK | MB_ICONEXCLAMATION);

		val = 65536;
		if (__argc >= 2) {
			val = atoi(__argv[1]);
		}

		ZeroMemory(&ans, sizeof(ans));
		ans.num = val;

		g_hd = CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)do_factorize,
				(LPVOID)&ans,
				0,
				&tid
				);

		break;

    case WM_DESTROY:
		// 若執行緒被啟動的話，則等候
		if (g_hd != NULL) {
			WaitForSingleObject(g_hd, INFINITE);
		}

        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

// main函數
int WINAPI WinMain(
  HINSTANCE hInstance,      //現在的實體標示元
  HINSTANCE hPrevInstance,  //以前的實體標示元
  LPSTR lpCmdLine,          //命令列
  int nCmdShow              //顯示狀態
) 
{
    MSG msg;
    WNDCLASSEX wc;
    HWND hWnd;

    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize           = sizeof(WNDCLASSEX); 
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.hInstance        = hInstance;
    wc.hCursor          = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName    = MYWNDCLASS;
    RegisterClassEx(&wc);  // 登錄視窗類別

    hWnd = CreateWindowEx(0, 
                MYWNDCLASS,
                "執行緒版質因數分解",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
                NULL,
                NULL,
                hInstance,
                NULL);
    ShowWindow(hWnd, nCmdShow);   // 描繪視窗

    while (GetMessage(&msg, NULL, 0, 0)) { // 訊息迴圈
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


