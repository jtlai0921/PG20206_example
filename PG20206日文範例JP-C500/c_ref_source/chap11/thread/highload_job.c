/*
 * 高負荷ジョブを実行する
 *
 * for compile:
 *  >cl highload_job.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <string.h>
#include <stdlib.h>

#define MYWNDCLASS  "MYWNDCLASS"


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
void do_factorize(int num, char *ans)
{
	char buf[8192], tmp[32]; // バッファ管理は手抜きｗ
	int n;

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

	strcpy(ans, buf);

	busy_wait();

	MessageBox(NULL, ans, "計算結果", MB_OK);
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int val;
	char ans[8192];

    switch (uMsg) {
	case WM_NCLBUTTONDBLCLK:
		MessageBox(NULL, "ダブルクリックされました", "お知らせ",
			MB_OK | MB_ICONEXCLAMATION);

		val = 65536;
		if (__argc >= 2) {
			val = atoi(__argv[1]);
		}

		do_factorize(val, ans);

		break;

    case WM_DESTROY:
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
                "素因数分解",
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


