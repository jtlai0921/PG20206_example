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
#define CAPTION     "Ū�J�I�}��"

#define WIDTH 320
#define HEIGHT 320


// ���JBMP��
void load_lena_image(HWND hWnd, HDC hdc)
{
	HDC hmdc;
	HBITMAP hBitmap;
	BITMAP bmp;
	HINSTANCE hInst;
	int bmp_w, bmp_h;


	// ���骺�Хܤ�
	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// �q�귽���J�I�}��
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// ���o�Ϲ����e�M��
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;

	// �s�@memory device context
	hmdc = CreateCompatibleDC(hdc);
	// ô��memory device context�M�I�}��
	SelectObject(hmdc, hBitmap);

	// �N�I�}�ϵe��ù�
	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	

	// ���񤣥Ϊ��귽
	DeleteDC(hmdc);
	DeleteObject(hBitmap);
}

// �����{��
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

// WinMain���
int WINAPI WinMain(HINSTANCE hInstance,	// �{�b���骺�Хܤ�
				   HINSTANCE hPrevInstance,	// �H�e���骺�Хܤ�
				   LPSTR lpCmdLine,	// �R�O�C
				   int nCmdShow	// ��ܪ��A
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
	RegisterClassEx(&wc);		// �n���������O

	hWnd = CreateWindowEx(0,
						  MYWNDCLASS,
						  CAPTION,
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, CW_USEDEFAULT,
						  WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);	// �yø����
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {	// �T���j��
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

