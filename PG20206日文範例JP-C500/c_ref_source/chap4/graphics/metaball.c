/*
 * 2D���^�{�[��
 *
 * for compile:
 *  >cl /O2 /nologo /W3 metaball.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "2D���^�{�[��"

#define WIDTH 480
#define HEIGHT 480


#define MAX 3    /* ���^�{�[���̐� */
/* ���^�{�[����� */
typedef struct {
	int x;   /* X�ʒu�i�f�J���g���W�j */
	int y;   /* Y�ʒu�i�f�J���g���W�j */
	double angle;  /* �p�x�� */
} point_t;

point_t balls[3];   


#define PI 3.141592

#define MAXPAL 256
DWORD palette[MAXPAL];   /* �p���b�g�e�[�u�� */
DWORD dwStartTime;   /* �J�n���� */
HWND hWndMain;       /* ���C���E�B���h�E�n���h�� */

/* �_�u���o�b�t�@�p�f�[�^ */
HDC offImgHDC;      
LPBITMAPINFO lpDIB;
LPBYTE lpBMP;
HBITMAP hBMP;

#define POS(x,y) ((x) + (y)*WIDTH)

#define RADIUS 70				// �{�[���̔��a
#define MAXPIXELS ((2*RADIUS)*(2*RADIUS))
/* �{�[���̉�f��� */
typedef struct {
	int x;     /* X�ʒu */
	int y;     /* Y�ʒu */
	int high;  /* (X,Y)�ɂ����鍂���i�F�f�j*/
} pixels_t;

pixels_t pixels[MAXPIXELS];


#if 0
int random(int val)
{
	double ret;

	ret = (1.0 / (RAND_MAX + 1.0)) * (rand() + 0.5);
	return ((int) (ret * val));
}
#endif

void put_pixel(int x, int y, DWORD color)
{
	int n, val;

	n = POS(x, y);
	if (n >= 0 && n < WIDTH * HEIGHT) {
		val = lpBMP[n * 3];
		val += GetBValue(color);
		if (val > 255)
			val = 255;
		lpBMP[n * 3] = val;

		val = lpBMP[n * 3 + 1];
		val += GetGValue(color);
		if (val > 255)
			val = 255;
		lpBMP[n * 3 + 1] = val;

		val = lpBMP[n * 3 + 2];
		val += GetRValue(color);
		if (val > 255)
			val = 255;
		lpBMP[n * 3 + 2] = val;
	}
}

void add_metaball(int dx, int dy)
{
	int x, y, cx, cy, i, n;

	/* �X�N���[�����W�֕ϊ����� */
	cx = dx + WIDTH / 2;
	cy = dy + HEIGHT / 2;

	for (i = 0; i < MAXPIXELS; i++) {
		x = cx + pixels[i].x;
		if (x < 0 || x > WIDTH)
			continue;
		y = cy + pixels[i].y;
		if (y < 0 || y > HEIGHT)
			continue;

		/* �{�[���̍������X�N���[���։��Z����B*/
		n = POS(x,y);
		if (n >= 0 && n < WIDTH*HEIGHT) {
			put_pixel(x, y, palette[pixels[i].high]);
		}
	}
}

void clear_screen(void)
{
	int i;

	/* �w�i�����œh��Ԃ� */
	for (i = 0 ; i < WIDTH*HEIGHT ; i++) {
		lpBMP[i * 3] = 0;
		lpBMP[i * 3 + 1] = 0;
		lpBMP[i * 3 + 2] = 0;
	}

	/* �����Ȃ����^�{�[�����������u�� */
	add_metaball(0, 0);
	add_metaball(100, 0);
	add_metaball(-100, -30);
	add_metaball(-200, 100);
}

void do_graphics(void)
{
	int i;
	double r, x, y;
	double angle;

	clear_screen();

	/* 1�߂̃{�[���i�A���L���f�X�̂点��j */
	angle = balls[0].angle;
	angle++;
	if (angle > 360*2)
		angle = 0;
	balls[0].angle = angle;
	r = 0.4 * angle;
	x = r * cos(angle * PI/180);
	y = r * sin(angle * PI/180);
	balls[0].x = (int)x;
	balls[0].y = (int)y;

	/* 2�߂̃{�[���i���T�[�W���Ȑ��j */
	angle = balls[1].angle;
	angle += 0.5;
	if (angle >= 360)
		angle = 0;
	balls[1].angle = angle;
	balls[1].x = (int)(WIDTH/3 * cos(3 * angle * PI/180));
	balls[1].y = (int)(WIDTH/3 * sin(5 * angle * PI/180));

	/* 3�߂̃{�[���i�ȉ~�Ȑ��j */
	angle = balls[2].angle;
	angle += 0.5;
	if (angle >= 360)
		angle = 0;
	balls[2].angle = angle;
	balls[2].x = (int)(WIDTH/2 * cos(angle * PI/180));
	balls[2].y = (int)(WIDTH/3 * sin(angle * PI/180));

	/* �S��ʂɂ�����{�[���̍������v�Z���� */
	for (i = 0; i < MAX; i++) {
		add_metaball(balls[i].x, balls[i].y);
	}
}

void do_effect(void)
{
	DWORD fps, now;
	static RECT rect = { 0, 0, WIDTH, HEIGHT };
	static char buf[128];

	// �t���[�����[�g�̌v�Z�i49.7�������͍l���Ȃ��j
	now = GetTickCount();
	if (now - dwStartTime <= 0)
		fps = 1000;
	else
		fps = 1000 / (now - dwStartTime);
	dwStartTime = now;
	wsprintf(buf, "%4d fps", fps);

	do_graphics();

	DrawText(offImgHDC, buf, -1, &rect, DT_LEFT);
	InvalidateRect(hWndMain, NULL, FALSE);
}


// �O���t�B�b�N�f�[�^�̏�����
void init_graphics(void)
{
	int i, x, y, r, c, val;
	double z, t;
	HDC hdc;

	// �{�[���̍������v�Z���āA�e��f�̐F�����肷��B
	r = RADIUS;
	c = 0;
	for (y = -r; y < r; y++) {
		for (x = -r; x < r; x++) {
			z = r * r - x * x - y * y;
			if (z < 0) {
				val = 0;

			} else {
				z = sqrt(z);
				t = z / r;
				val = (int)(MAXPAL * (t * t * t * t));

				if (val > 255)
					val = 255;
				if (val < 0)
					val = 0;
			}

			assert(c < MAXPIXELS);
			pixels[c].x = x;
			pixels[c].y = y;
			pixels[c].high = val;
			c++;

			//printf("(%d,%d,%f) = %d\n", x, y, z, val);
		}
	}

	for (i = 0 ; i < MAX ; i++) {
		balls[i].x = 0;
		balls[i].y = 0;
		balls[i].angle = 0;
	}

	// �p���b�g�̍쐬
	{
		int r, g, b;
		for (i = 0; i < MAXPAL; i++) {
			r = g = b = 0;
			if (i >= 0)
				b = 4 * i;
			if (i >= 2)
				g = 4 * (i / 2);
			if (i >= 4)
				r = 4 * (i / 4);

			if (r > 255)
				r = 255;
			if (g > 255)
				g = 255;
			if (b > 255)
				b = 255;

			palette[i] = RGB(r, g, b);

			//printf("{%d,%d,%d}\n", r, g, b);
		}
	}

	// �J�n���ԁi�~���b�j
	dwStartTime = GetTickCount();

	// �_�u���o�b�t�@�̍쐬
	hdc = GetDC(hWndMain);
	lpDIB = (LPBITMAPINFO) GlobalAlloc(GPTR, sizeof(BITMAPINFO));	/* �c�h�a�p�������m�� */

	/* DIBSection �pBITMAPINFO�\���̐ݒ� */
	ZeroMemory(&lpDIB->bmiHeader, sizeof(lpDIB->bmiHeader));
	lpDIB->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpDIB->bmiHeader.biWidth = WIDTH;
	lpDIB->bmiHeader.biHeight = HEIGHT;
	lpDIB->bmiHeader.biPlanes = 1;
	lpDIB->bmiHeader.biBitCount = 24;
	lpDIB->bmiHeader.biCompression = BI_RGB;
	lpDIB->bmiHeader.biSizeImage = 0;
	lpDIB->bmiHeader.biXPelsPerMeter = 0;
	lpDIB->bmiHeader.biYPelsPerMeter = 0;
	lpDIB->bmiHeader.biClrUsed = 0;
	lpDIB->bmiHeader.biClrImportant = 0;

	hBMP = CreateDIBSection(hdc, lpDIB, DIB_RGB_COLORS, &lpBMP, NULL, 0);
	offImgHDC = CreateCompatibleDC(hdc);	/* ������DC ���쐬 */
	SelectObject(offImgHDC, hBMP);	/* ������DC ��DIBSection��I�� */

	ReleaseDC(hWndMain, hdc);
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
						 LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (uMsg) {
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, offImgHDC, 0, 0, SRCCOPY);
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

// ���C���֐�
int WINAPI WinMain(HINSTANCE hInstance,	// ���݂̃C���X�^���X�̃n���h��
				   HINSTANCE hPrevInstance,	// �ȑO�̃C���X�^���X�̃n���h��
				   LPSTR lpCmdLine,	// �R�}���h���C��
				   int nCmdShow	// �\�����
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
	RegisterClassEx(&wc);		// �E�B���h�E�N���X�̓o�^

	hWnd = CreateWindowEx(0,
						  MYWNDCLASS,
						  CAPTION,
						  WS_OVERLAPPEDWINDOW,
						  CW_USEDEFAULT, CW_USEDEFAULT,
						  WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

	hWndMain = hWnd;
	init_graphics();

	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕`��
	UpdateWindow(hWnd);

	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == 0) {	// ���b�Z�[�W���Ȃ�
			do_effect();

		} else {
			if (GetMessage(&msg, NULL, 0, 0) == 0) {
				return msg.wParam;
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return msg.wParam;
}


int main(void)
{
	init_graphics();
	do_effect();

	return 0;
}

