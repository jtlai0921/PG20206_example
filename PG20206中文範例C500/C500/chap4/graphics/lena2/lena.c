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
#define CAPTION     "Lena���Ϲ��B�z"

#define WIDTH 312*2
#define HEIGHT 312*2


// ���ɧJ
void do_mosaic(LPBYTE lpBMP, int width, int height)
{
	int bs = 8; // �϶��j�p
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


// �N�Ϲ��C�����
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

// �@�H��
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
		if (gray > 255) //���M�t��
			gray = 255;

		lpBMP[i * 3] = (BYTE) gray;
		lpBMP[i * 3 + 1] = (BYTE) gray;
		lpBMP[i * 3 + 2] = (BYTE) gray;
	}
}

// ���J�I�}��
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
//  hBitmap = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);   // �o�O�ª�API
	// �N�I�}�ϸ��J��O����
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// ���o�Ϲ����e�שM����
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;
	hmdc = CreateCompatibleDC(hdc);

	// �ϥΰ}�C�Ӧs���ù�(hdc)���U�ӹ���
	lpDIB = (LPBITMAPINFO) GlobalAlloc(GPTR, sizeof(BITMAPINFO));	/* �T�ODIB�Ϊ��O���� */

	/* DIBSection�Ϊ�BITMAPINFO���c�]�w */
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
	hdcMem = CreateCompatibleDC(hdc);	/* �s�@Memory device context */
	SelectObject(hdcMem, hBMP);	/* Memory device context�PDIBSection��ô�� */

	// �N�ù��M�I�}�ϰ�ô��
	SelectObject(hmdc, hBitmap);

	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	// ��Ϲ�

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_gray_scale(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, bmp_w, 0, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// �@�H�ƹϹ�

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_reverse(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, 0, bmp_h, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// ����Ϲ�
//  BitBlt(hdc, 0, bmp_h, bmp_w, bmp_h, hmdc, 0, 0, NOTSRCCOPY); // ����Ϲ�

	BitBlt(hdcMem, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);
	do_mosaic(lpBMP, bmp_w, bmp_h);
	BitBlt(hdc, bmp_w, bmp_h, bmp_w, bmp_h, hdcMem, 0, 0, SRCCOPY);	// ���ɧJ


	// ���񤣭n���귽
	DeleteDC(hmdc);
	DeleteObject(hBitmap);

	DeleteDC(hdcMem);
	DeleteObject(hBMP);
	GlobalFree(lpDIB);
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
int WINAPI WinMain(HINSTANCE hInstance,	// �{�b�����骺�Хܤ�
				   HINSTANCE hPrevInstance,	// �H�e�����骺�Хܤ�
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
