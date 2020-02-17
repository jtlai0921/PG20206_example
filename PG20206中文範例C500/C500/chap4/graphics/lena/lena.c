/*
 * lena.c
 *
 * for compile:
 *  >rc lena2.rc
 *  >cl /nologo /W3 lena.c lena2.res user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
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
#define CAPTION     "讀入點陣圖"

#define WIDTH 320
#define HEIGHT 320


// 載入BMP檔
void load_lena_image(HWND hWnd, HDC hdc)
{
	HDC hmdc;
	HBITMAP hBitmap;
	BITMAP bmp;
	HINSTANCE hInst;
	int bmp_w, bmp_h;


	// 實體的標示元
	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// 從資源載入點陣圖
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// 取得圖像的寬和高
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;

	// 製作memory device context
	hmdc = CreateCompatibleDC(hdc);
	// 繫結memory device context和點陣圖
	SelectObject(hmdc, hBitmap);

	// 將點陣圖畫到螢幕
	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	

	// 釋放不用的資源
	DeleteDC(hmdc);
	DeleteObject(hBitmap);
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

