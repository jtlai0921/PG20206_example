/*
 * lena.c
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "Lena的圖像處理"

#define WIDTH 312*2
#define HEIGHT 312*2


// 馬賽克
void do_mosaic(LPBYTE lpBMP, int width, int height)
{
	int bs = 8; // 區塊大小
	int x, y, i, j, pos, n;
	int r, g, b;

	for (y = 0; y < height / bs; y++) {
		for (x = 0; x < width / bs; x++) {
			pos = (x * bs) + (y * bs) * width;
			b = lpBMP[pos * 3];
			g = lpBMP[pos * 3 + 1];
			r = lpBMP[pos * 3 + 2];

			for (j = 0; j < bs; j++) {
				for (i = 0; i < bs; i++) {
					n = pos + (i + j * width);
					lpBMP[n * 3] = b;
					lpBMP[n * 3 + 1] = g;
					lpBMP[n * 3 + 2] = r;
				}
			}

		}
	}

}


// 將圖像顏色反轉
void do_reverse(LPBYTE lpBMP, int width, int height)
{
	int i;
	int r, g, b;

	for (i = 0; i < width * height; i++) {
		b = lpBMP[i * 3];
		g = lpBMP[i * 3 + 1];
		r = lpBMP[i * 3 + 2];
		lpBMP[i * 3] = b ^ 0xff;
		lpBMP[i * 3 + 1] = g ^ 0xff;
		lpBMP[i * 3 + 2] = r ^ 0xff;
	}
}

// 濃淡化
void do_gray_scale(LPBYTE lpBMP, int width, int height)
{
	int i;
	int r, g, b;
	double gray;

	for (i = 0; i < width * height; i++) {
		b = lpBMP[i * 3];
		g = lpBMP[i * 3 + 1];
		r = lpBMP[i * 3 + 2];
		gray = 0.299 * r + 0.587 * g + 0.114 * b;
		if (gray > 255) //飽和演算
			gray = 255;

		lpBMP[i * 3] = (BYTE) gray;
		lpBMP[i * 3 + 1] = (BYTE) gray;
		lpBMP[i * 3 + 2] = (BYTE) gray;
	}
}

// 載入點陣圖
void load_lena_image(HWND hWnd, HDC hdc)
{
	HDC hmdc;
	HBITMAP hBitmap;
	BITMAP bmp;
	HINSTANCE hInst;
	int bmp_w, bmp_h;

	LPBITMAPINFO lpDIB;
	LPBYTE lpBMP;
	HBITMAP hBMP;
	HDC hdcMem;


	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
//  hBitmap = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);   // 這是舊的API
	// 將點陣圖載入到記憶體
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// 取得圖像的寬度和高度
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;
	hmdc = CreateCompatibleDC(hdc);

	// 使用陣列來存取螢幕(hdc)的各個像素
	lpDIB = (LPBITMAPINFO) GlobalAlloc(GPTR, sizeof(BITMAPINFO));	/* 確保DIB用的記憶體 */

	/* DIBSection用的BITMAPINFO結構設定 */
	ZeroMemory(&lpDIB->bmiHeader, sizeof(lpDIB->bmiHeader));
	lpDIB->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpDIB->bmiHeader.biWidth = bmp_w;
	lpDIB->bmiHeader.biHeight = bmp_h;
	lpDIB->bmiHeader.biPlanes = 1;
	lpDIB->bmiHeader.biBitCount = 24;
	lpDIB->bmiHeader.biCompression = BI_RGB;
	lpDIB->bmiHeader.biSizeImage = 0;
	lpDIB->bmiHeader.biXPelsPerMeter = 0;
	lpDIB->bmiHeader.biYPelsPerMeter = 0;
	lpDIB->bmiHeader.biClrUsed = 0;
	lpDIB->bmiHeader.biClrImportant = 0;

	hBMP = CreateDIBSection(hdc, lpDIB, DIB_RGB_COLORS, &lpBMP, NULL, 0);
	hdcMem = CreateCompatibleDC(hdc);	/* 製作Memory device context */
	SelectObject(hdcMem, hBMP);	/* Memory device context與DIBSection的繫結 */

	// 將螢幕和點陣圖做繫結
	SelectObject(hmdc, hBitmap);

	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	// 原圖像

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_gray_scale(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, bmp_w, 0, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// 濃淡化圖像

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_reverse(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, 0, bmp_h, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// 反轉圖像
//  BitBlt(hdc, 0, bmp_h, bmp_w, bmp_h, hmdc, 0, 0, NOTSRCCOPY); // 反轉圖像

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_mosaic(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, bmp_w, bmp_h, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// 馬賽克


	// 釋放不要的資源
	DeleteDC(hmdc);
	DeleteObject(hBitmap);

	DeleteDC(hdcMem);
	DeleteObject(hBMP);
	GlobalFree(lpDIB);
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
		load_lena_image(hWnd, hdc);
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

// WinMain函數
int WINAPI WinMain(HINSTANCE hInstance,	// 現在的實體的標示元
				   HINSTANCE hPrevInstance,	// 以前的實體的標示元
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
