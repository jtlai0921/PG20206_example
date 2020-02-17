/*
 * ∞ı¶Ê∞™≠t≤¸™∫ß@∑~
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
// ®D•XΩË¶]º∆§¿∏—
//
void do_factorize(int num, char *ans)
{
	char buf[8192], tmp[32]; // ΩwΩƒ∞œ∫ﬁ≤z≥°§¿∞Ω√i§@§U
	int n;

	sprintf(buf, "%d=", num);

	// •Œ2∞£®Ï§£Ø‡¶A∞£
	while (num >= 4) {
		if (num % 2)
			break;
		num /= 2;
		strcat(buf, "2Å~");
	}

	// •Œ3•H§W™∫©_º∆•h∞£
	n = 3;
	while (n * n <= num) {
		if (num % n)
			n += 2;  // ¥´§U§@≠”©_º∆

		num /= n;

		sprintf(tmp, "%dÅ~", n);
		strcat(buf, tmp);
	}
	sprintf(tmp, "%d", num);
	strcat(buf, tmp);

	strcpy(ans, buf);

	busy_wait();

	MessageBox(NULL, ans, "≠p∫‚µ≤™G", MB_OK);
}

// µ¯µ°µ{ß«
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int val;
	char ans[8192];

    switch (uMsg) {
	case WM_NCLBUTTONDBLCLK:
		MessageBox(NULL, "∑∆π´¬I´ˆ§F§G§U", "≥q™æ",
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

// main®Áº∆
int WINAPI WinMain(
  HINSTANCE hInstance,      // ≤{¶b™∫πÍ≈Èº–•‹§∏
  HINSTANCE hPrevInstance,  // •H´e™∫πÍ≈Èº–•‹§∏
  LPSTR lpCmdLine,          // ©R•O¶C
  int nCmdShow              // ≈„•‹™¨∫A
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
    RegisterClassEx(&wc);  // µnø˝µ¯µ°√˛ßO

    hWnd = CreateWindowEx(0, 
                MYWNDCLASS,
                "ΩË¶]º∆§¿∏—",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
                NULL,
                NULL,
                hInstance,
                NULL);
    ShowWindow(hWnd, nCmdShow);   // ¥y√∏µ¯µ°

    while (GetMessage(&msg, NULL, 0, 0)) { // ∞TÆß∞j∞È
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


