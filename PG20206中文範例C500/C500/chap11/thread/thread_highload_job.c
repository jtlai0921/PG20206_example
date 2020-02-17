/*
 * �ϥΦh������Ӱ��氪�t�����@�~
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
// �D�X��]�Ƥ���
//
void do_factorize(ans_t *ans)
{
	char buf[8192], tmp[32]; // �w�İϺ޲z�������i�@�U
	int n;
	int num;

	num = ans->num;

	sprintf(buf, "%d=", num);

	// ��2���줣��A��
	while (num >= 4) {
		if (num % 2)
			break;
		num /= 2;
		strcat(buf, "2�~");
	}

	// ��3�H�W���_�ƥh��
	n = 3;
	while (n * n <= num) {
		if (num % n)
			n += 2;  // ���U�@�ө_��

		num /= n;

		sprintf(tmp, "%d��", n);
		strcat(buf, tmp);
	}
	sprintf(tmp, "%d", num);
	strcat(buf, tmp);

	strcpy(ans->ans, buf);

	busy_wait();

	MessageBox(NULL, ans->ans, "�p�⵲�G", MB_OK);
}

// �����{��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int val;
	ans_t ans;
	DWORD tid;

    switch (uMsg) {
	case WM_NCLBUTTONDBLCLK:
		MessageBox(NULL, "�ƹ��I���F�G�U", "�q��",
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
		// �Y������Q�Ұʪ��ܡA�h����
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

// main���
int WINAPI WinMain(
  HINSTANCE hInstance,      //�{�b������Хܤ�
  HINSTANCE hPrevInstance,  //�H�e������Хܤ�
  LPSTR lpCmdLine,          //�R�O�C
  int nCmdShow              //��ܪ��A
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
    RegisterClassEx(&wc);  // �n���������O

    hWnd = CreateWindowEx(0, 
                MYWNDCLASS,
                "���������]�Ƥ���",
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
                NULL,
                NULL,
                hInstance,
                NULL);
    ShowWindow(hWnd, nCmdShow);   // �yø����

    while (GetMessage(&msg, NULL, 0, 0)) { // �T���j��
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


