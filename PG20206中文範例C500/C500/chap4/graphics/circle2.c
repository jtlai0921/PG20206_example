/*
 * 用點畫出球體
 *
 * for compile:
 *  >cl circle2.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
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
#define CAPTION     "點畫(附陰影)"

#define WIDTH 480
#define HEIGHT 480


/* 在畫面上畫點 */
void draw_dot_point(HWND hWnd, HDC hdc, double x, double y, int col) 
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;

	/* 移動到畫面中心 */
	x += WIDTH / 2;
	y += HEIGHT / 2;

	rt.left = (LONG)x - 1;
	rt.top = (LONG)y - 1;
	rt.right = (LONG)x + 1;
	rt.bottom = (LONG)y + 1;

	/* 產生筆刷 */
	hBrush = CreateSolidBrush(RGB(col, col, col));
	hOldBrush = SelectObject(hdc, hBrush);

	/* 繪出四方形 */
	FillRect(hdc, &rt, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void do_graphics(HWND hWnd, HDC hdc) 
{
	double x, y, z, val, max, min;
	int rlen, col;
	double light[3] = {-2.0, -2.0, 9.0};
	double lvec[3], nl, lval, nvec[3];

	rlen = 300 / 2;   // 球的半徑
	min = -rlen;
	max = rlen;

	/* 計算法線向量 */
	nl = sqrt(light[0]*light[0] + light[1]*light[1] +  light[2]*light[2]);
	lvec[0] = light[0] / nl;
	lvec[1] = light[1] / nl;
	lvec[2] = light[2] / nl;

	for (y = min ; y < max ; y += 2) {
		for (x = min ; x < max ; x += 2) {
			val = rlen*rlen - x*x - y*y;
			if (val < 0)
				continue;

			z = sqrt(val);

			nvec[0] = x / rlen;
			nvec[1] = y / rlen;
			nvec[2] = z / rlen;
			lval = lvec[0]*nvec[0] + lvec[1]*nvec[1] + lvec[2]*nvec[2];

			/* 計算光的量 */
			lval = (light[0]*x + light[1]*y + light[2]*z) / (nl * rlen);

			col = 240 * lval;

			if (col > 255)
				col = 255;
			if (col < 0)
				col = 0;

			printf("x %f y %f z %f -> col %d\n", x, y, z, col);

			draw_dot_point(hWnd, hdc, x, y, col);
		}
	}
}

// 視窗程序
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

// Main函數
int WINAPI WinMain(
  HINSTANCE hInstance,      // 現在實體的標示元
  HINSTANCE hPrevInstance,  // 以前實體的標示元
  LPSTR lpCmdLine,          // 命令列
  int nCmdShow              // 顯示狀態
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
    RegisterClassEx(&wc);  // 登錄視窗類別

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
    ShowWindow(hWnd, nCmdShow);   // 描繪視窗
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // 訊息迴圈
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


int main(void)
{
	do_graphics(NULL, NULL);

	return 0;
}


