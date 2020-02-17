/*
 * Lissajous���u
 *
 * for compile:
 * >cl /W3 /nologo lissajous.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "Lissajous���u"

#define WIDTH 480
#define HEIGHT 480

#define RADIAN 3.141592/180.0
#define RADIUS 200


/* �b�e���W�e�I */
void draw_dot_point(HWND hWnd, HDC hdc, double x, double y, int col) 
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;

	/* ���ʨ�e������ */
	x += WIDTH / 2;
	y += HEIGHT / 2;

	rt.left = (LONG)x - 1;
	rt.top = (LONG)y - 1;
	rt.right = (LONG)x + 1;
	rt.bottom = (LONG)y + 1;

	/* ���͵��� */
	hBrush = CreateSolidBrush(RGB(col, col, col));
	hOldBrush = SelectObject(hdc, hBrush);

	/* ø�X�|��� */
	FillRect(hdc, &rt, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

/* Lissajous���u: x=sin(6�c) y=sin(7�c) */
void sub3(double ang, double *x, double *y)
{
	*x = RADIUS * sin(6 * ang * RADIAN);
	*y = RADIUS * sin(7 * ang * RADIAN);
}

/* Lissajous���u: x=cos(3�c) y=sin(5�c) */
void sub2(double ang, double *x, double *y)
{
	*x = RADIUS * cos(3 * ang * RADIAN);
	*y = RADIUS * sin(5 * ang * RADIAN);
}

/* Lissajous���u: x=cos(5�c) y=cos(3�c) */
void sub(double ang, double *x, double *y)
{
	*x = RADIUS * cos(5 * ang * RADIAN);
	*y = RADIUS * cos(3 * ang * RADIAN);
}

void do_lissajous(HWND hWnd, HDC hdc) 
{
	double x, y, max, min;
	double ang;
	int rlen, col, no;

	void (*func_table[])(double, double*, double*) = {
		sub,
		sub2,
		sub3,
	};

	no = 0;
	if (__argc > 1) {
		no = atoi(__argv[1]);
		if (no >= 3)
			no = 0;
	}

	rlen = 300 / 2;
	min = -rlen;
	max = rlen;

	for (ang = 0 ; ang < 360; ang += 0.25) {
		func_table[no](ang, &x, &y);

		col = 255;
		draw_dot_point(hWnd, hdc, x, y, col);
	}
}

// �����{��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

    switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		do_lissajous(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

// Main���
int WINAPI WinMain(
  HINSTANCE hInstance,      // �{�b���骺�Хܤ�
  HINSTANCE hPrevInstance,  // �H�e���骺�Хܤ�
  LPSTR lpCmdLine,          // �R�O�C
  int nCmdShow              // ��ܪ��A
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
    wc.hbrBackground    =  GetStockObject(BLACK_BRUSH);
    wc.lpszClassName    = MYWNDCLASS;
    RegisterClassEx(&wc);  // �n���������O

    hWnd = CreateWindowEx(0, 
                MYWNDCLASS,
                CAPTION,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, 
				WIDTH, HEIGHT,
                NULL,
                NULL,
                hInstance,
                NULL);
    ShowWindow(hWnd, nCmdShow);   // �yø����
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // �T���j��
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


int main(void)
{

	return 0;
}


