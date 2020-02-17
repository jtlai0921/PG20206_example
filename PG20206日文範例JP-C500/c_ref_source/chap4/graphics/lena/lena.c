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
#define CAPTION     "ビットマップ画像の読み込み"

#define WIDTH 320
#define HEIGHT 320


// BMP画像をロードする
void load_lena_image(HWND hWnd, HDC hdc)
{
	HDC hmdc;
	HBITMAP hBitmap;
	BITMAP bmp;
	HINSTANCE hInst;
	int bmp_w, bmp_h;


	// インスタンスのハンドル
	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// リソースからビットマップ画像をロード
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// 画像の横と縦のサイズを取得する
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;

	// メモリデバイスコンテキストの作成
	hmdc = CreateCompatibleDC(hdc);
	// メモリデバイスコンテキストとビットマップ画像をバインドする
	SelectObject(hmdc, hBitmap);

	// ビットマップ画像をスクリーンへ描画する
	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	

	// 不要なリソースを解放する
	DeleteDC(hmdc);
	DeleteObject(hBitmap);
}

// ウィンドウプロシージャ
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

// メイン関数
int WINAPI WinMain(HINSTANCE hInstance,	// 現在のインスタンスのハンドル
				   HINSTANCE hPrevInstance,	// 以前のインスタンスのハンドル
				   LPSTR lpCmdLine,	// コマンドライン
				   int nCmdShow	// 表示状態
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
	RegisterClassEx(&wc);		// ウィンドウクラスの登録

	hWnd = CreateWindowEx(0,
						  MYWNDCLASS,
						  CAPTION,
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, CW_USEDEFAULT,
						  WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);	// ウィンドウの描画
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {	// メッセージループ
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

