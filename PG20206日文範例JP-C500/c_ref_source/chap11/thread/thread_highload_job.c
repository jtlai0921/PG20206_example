/*
 * マルチスレッドを使って高負荷ジョブを実行する
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
// 素因数分解を求める
//
void do_factorize(ans_t *ans)
{
	char buf[8192], tmp[32]; // バッファ管理は手抜きｗ
	int n;
	int num;

	num = ans->num;

	sprintf(buf, "%d=", num);

	// 2で割れるところまで割り切る
	while (num >= 4) {
		if (num % 2)
			break;
		num /= 2;
		strcat(buf, "2×");
	}

	// 3以上の奇数で割っていく
	n = 3;
	while (n * n <= num) {
		if (num % n)
			n += 2;  // 次の奇数へ

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

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int val;
	ans_t ans;
	DWORD tid;

    switch (uMsg) {
	case WM_NCLBUTTONDBLCLK:
		MessageBox(NULL, "ダブルクリックされました", "お知らせ",
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
		// スレッドが起こされていれば待ち合わせをする
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

// メイン関数
int WINAPI WinMain(
  HINSTANCE hInstance,      // 現在のインスタンスのハンドル
  HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
  LPSTR lpCmdLine,          // コマンドライン
  int nCmdShow              // 表示状態
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
    RegisterClassEx(&wc);  // ウィンドウクラスの登録

    hWnd = CreateWindowEx(0, 
                MYWNDCLASS,
                "スレッド版素因数分解",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
                NULL,
                NULL,
                hInstance,
                NULL);
    ShowWindow(hWnd, nCmdShow);   // ウィンドウの描画

    while (GetMessage(&msg, NULL, 0, 0)) { // メッセージループ
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


