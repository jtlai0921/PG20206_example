/*
 * ��
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
#define CAPTION     "��"

#define WIDTH 480
#define HEIGHT 480

#define RADIAN 3.141592/180.0
#define RADIUS 200


/* �N�����}�C�ϬM��ù��W */
void draw_pixel_screen(HDC hdc, int pixels[], int width, int height,
					   int palette[])
{
	LPBITMAPINFO lpDIB;
	LPBYTE lpBMP;
	HBITMAP hBMP;
	HDC hdcMem;
	int i, val;

	lpDIB = (LPBITMAPINFO) GlobalAlloc(GPTR, sizeof(BITMAPINFO));	/* �T�ODIB�O���� */

	/* DIBSection�Ϊ�BITMAPINFO���c�]�w */
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
	hdcMem = CreateCompatibleDC(hdc);	/* �s�@memory device context */
	SelectObject(hdcMem, hBMP);	/* memory device context�PDIBSection��ô�� */

	/* �N�����Ȧs���I�}�� */
	for (i = 0; i < width * height; i++) {
		val = pixels[i];
		lpBMP[i * 3] = GetBValue(palette[val]);
		lpBMP[i * 3 + 1] = GetGValue(palette[val]);
		lpBMP[i * 3 + 2] = GetRValue(palette[val]);
	}

	/* �q�I�}�ϱN��ƶǰe��ù� */
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

	/* �զ�L���]�w */
	for (i = 0; i < PALMAX; i++) {
		palette[i] = RGB(i, 128 + i / 3, 255);
	}

	bs = 80;					// �϶��j�p

	do {
		for (y = 0; y < HEIGHT / bs; y++) {
			for (x = 0; x < WIDTH / bs; x++) {

				/* �M�w�C�� */
				if (bs == 80) {
					col = random(PALMAX);
				} else {
					/* �W */
					nx = x * bs;
					if (y - 1 < 0)
						ny = HEIGHT / bs - 1;
					else
						ny = (y - 1) * bs;
					col = pixels[pos(nx, ny)];

					/* �k */
					if (x + 1 >= WIDTH / bs)
						nx = 0;
					else
						nx = (x + 1) * bs;
					ny = y * bs;
					col += pixels[pos(nx, ny)];

					/* �U */
					nx = x * bs;
					if (y + 1 >= HEIGHT / bs)
						ny = 0;
					else
						ny = (y + 1) * bs;
					col += pixels[pos(nx, ny)];

					/* �� */
					if (x - 1 < 0)
						nx = WIDTH / bs - 1;
					else
						nx = (x - 1) * bs;
					ny = y * bs;
					col += pixels[pos(nx, ny)];

					col /= 4;	/* ������ */
				}

				printf("col %d\n", col);

				/* �N�϶�� */
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

// �����{��
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

// Main���
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


int main(void)
{
	do_graphics(NULL, NULL);

	return 0;
}
