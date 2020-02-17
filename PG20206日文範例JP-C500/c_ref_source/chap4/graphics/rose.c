/*
 * バラ曲線
 *
 * for compile:
 * >cl /W3 /nologo rose.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
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
#define CAPTION     "バラ曲線"

#define WIDTH 480
#define HEIGHT 480

#define RADIAN 3.141592/180.0
#define RADIUS 200


/* 画面に点を描画する */
void draw_dot_point(HWND hWnd, HDC hdc, double x, double y, int col) 
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;

	/* 画面の中心へ持っていく */
	x += WIDTH / 2;
	y += HEIGHT / 2;

	rt.left = (LONG)x - 1;
	rt.top = (LONG)y - 1;
	rt.right = (LONG)x + 1;
	rt.bottom = (LONG)y + 1;

	/* ブラシの作成 */
	hBrush = CreateSolidBrush(RGB(col, col, col));
	hOldBrush = SelectObject(hdc, hBrush);

	/* 四角形の描画 */
	FillRect(hdc, &rt, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

/* バラ曲線： r=a・sin(kθ) */
void sub4(double ang, double *x, double *y)
{
	double r;

	r = 1 * sin(5*ang*RADIAN);

	*x = RADIUS * r * cos(ang * RADIAN);
	*y = RADIUS * r * sin(ang * RADIAN);
}

/* バラ曲線： r=a・sin(kθ) */
void sub3(double ang, double *x, double *y)
{
	double r;

	r = 1 * sin(4*ang*RADIAN);

	*x = RADIUS * r * cos(ang * RADIAN);
	*y = RADIUS * r * sin(ang * RADIAN);
}

/* バラ曲線： r=a・sin(kθ) */
void sub2(double ang, double *x, double *y)
{
	double r;

	r = 1 * sin(3*ang*RADIAN);

	*x = RADIUS * r * cos(ang * RADIAN);
	*y = RADIUS * r * sin(ang * RADIAN);
}

/* バラ曲線： r=a・sin(kθ) */
void sub(double ang, double *x, double *y)
{
	double r;

	r = 1 * sin(2*ang*RADIAN);

	*x = RADIUS * r * cos(ang * RADIAN);
	*y = RADIUS * r * sin(ang * RADIAN);
}

void do_graphics(HWND hWnd, HDC hdc) 
{
	double x, y, max, min;
	double ang;
	int rlen, col, no;

	void (*func_table[])(double, double*, double*) = {
		sub,
		sub2,
		sub3,
		sub4,
	};

	no = 0;
	if (__argc > 1) {
		no = atoi(__argv[1]);
		if (no >= 4)
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

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

    switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		do_graphics(hWnd, hdc);
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
    wc.hbrBackground    =  GetStockObject(BLACK_BRUSH);
    wc.lpszClassName    = MYWNDCLASS;
    RegisterClassEx(&wc);  // ウィンドウクラスの登録

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
    ShowWindow(hWnd, nCmdShow);   // ウィンドウの描画
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // メッセージループ
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


int main(void)
{

	return 0;
}


