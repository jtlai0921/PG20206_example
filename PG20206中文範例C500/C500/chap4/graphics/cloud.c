/*
 * 雲
 *
 * for compile:
 * >cl /W3 /nologo cloud.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
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
#define CAPTION     "雲"

#define WIDTH 480
#define HEIGHT 480

#define RADIAN 3.141592/180.0
#define RADIUS 200


/* 將像素陣列反映到螢幕上 */
void draw_pixel_screen(HDC hdc, int pixels[], int width, int height,
					   int palette[])
{
	LPBITMAPINFO lpDIB;
	LPBYTE lpBMP;
	HBITMAP hBMP;
	HDC hdcMem;
	int i, val;

	lpDIB = (LPBITMAPINFO) GlobalAlloc(GPTR, sizeof(BITMAPINFO));	/* 確保DIB記憶體 */

	/* DIBSection用的BITMAPINFO結構設定 */
	lpDIB->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpDIB->bmiHeader.biWidth = width;
	lpDIB->bmiHeader.biHeight = height;
	lpDIB->bmiHeader.biPlanes = 1;
	lpDIB->bmiHeader.biBitCount = 24;
	lpDIB->bmiHeader.biCompression = BI_RGB;
	lpDIB->bmiHeader.biSizeImage = 0;
	lpDIB->bmiHeader.biXPelsPerMeter = 0;
	lpDIB->bmiHeader.biYPelsPerMeter = 0;
	lpDIB->bmiHeader.biClrUsed = 0;
	lpDIB->bmiHeader.biClrImportant = 0;

	hBMP = CreateDIBSection(hdc, lpDIB, DIB_RGB_COLORS, &lpBMP, NULL, 0);
	hdcMem = CreateCompatibleDC(hdc);	/* 製作memory device context */
	SelectObject(hdcMem, hBMP);	/* memory device context與DIBSection的繫結 */

	/* 將像素值存到點陣圖 */
	for (i = 0; i < width * height; i++) {
		val = pixels[i];
		lpBMP[i * 3] = GetBValue(palette[val]);
		lpBMP[i * 3 + 1] = GetGValue(palette[val]);
		lpBMP[i * 3 + 2] = GetRValue(palette[val]);
	}

	/* 從點陣圖將資料傳送到螢幕 */
	BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

	DeleteDC(hdcMem);
	DeleteObject(hBMP);
	GlobalFree(lpDIB);
}


int random(int val)
{
	double ret;

	ret = (1.0 / (RAND_MAX + 1.0)) * (rand() + 0.5);
	return ((int) (ret * val));
}

void do_graphics(HWND hWnd, HDC hdc)
{
#define pos(x,y) ((x) + (y)*WIDTH)
#define PALMAX 256
	int col;
	int pixels[WIDTH * HEIGHT];
	int bs, i, j, x, y;
	int nx, ny;
	DWORD palette[PALMAX];

	srand(GetTickCount());

	/* 調色盤的設定 */
	for (i = 0; i < PALMAX; i++) {
		palette[i] = RGB(i, 128 + i / 3, 255);
	}

	bs = 80;					// 區塊大小

	do {
		for (y = 0; y < HEIGHT / bs; y++) {
			for (x = 0; x < WIDTH / bs; x++) {

				/* 決定顏色 */
				if (bs == 80) {
					col = random(PALMAX);
				} else {
					/* 上 */
					nx = x * bs;
					if (y - 1 < 0)
						ny = HEIGHT / bs - 1;
					else
						ny = (y - 1) * bs;
					col = pixels[pos(nx, ny)];

					/* 右 */
					if (x + 1 >= WIDTH / bs)
						nx = 0;
					else
						nx = (x + 1) * bs;
					ny = y * bs;
					col += pixels[pos(nx, ny)];

					/* 下 */
					nx = x * bs;
					if (y + 1 >= HEIGHT / bs)
						ny = 0;
					else
						ny = (y + 1) * bs;
					col += pixels[pos(nx, ny)];

					/* 左 */
					if (x - 1 < 0)
						nx = WIDTH / bs - 1;
					else
						nx = (x - 1) * bs;
					ny = y * bs;
					col += pixels[pos(nx, ny)];

					col /= 4;	/* 平均化 */
				}

				printf("col %d\n", col);

				/* 將區塊塗滿 */
				for (j = y * bs; j < y * bs + bs; j++) {
					for (i = x * bs; i < x * bs + bs; i++) {
						pixels[pos(i, j)] = col;
					}
				}

			}
		}

		bs /= 2;
	} while (bs > 0);

	draw_pixel_screen(hdc, pixels, WIDTH, HEIGHT, palette);
}

// 視窗程序
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
						 LPARAM lParam)
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
int WINAPI WinMain(HINSTANCE hInstance,	// 現在實體的標示元
				   HINSTANCE hPrevInstance,	// 以前實體的標示元
				   LPSTR lpCmdLine,	// 命令列
				   int nCmdShow	// 顯示狀態
	)
{
	MSG msg;
	WNDCLASSEX wc;
	HWND hWnd;

	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wc.hbrBackground = GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = MYWNDCLASS;
	RegisterClassEx(&wc);		// 登錄視窗類別

	hWnd = CreateWindowEx(0,
						  MYWNDCLASS,
						  CAPTION,
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, CW_USEDEFAULT,
						  WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);	// 描繪視窗
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {	// 訊息迴圈
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
