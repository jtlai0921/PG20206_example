/*
 * �h�b�g�ŋ���`��
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
#define CAPTION     "�_�`(�A�e�t��)"

#define WIDTH 480
#define HEIGHT 480


/* ��ʂɓ_��`�悷�� */
void draw_dot_point(HWND hWnd, HDC hdc, double x, double y, int col) 
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;

	/* ��ʂ̒��S�֎����Ă��� */
	x += WIDTH / 2;
	y += HEIGHT / 2;

	rt.left = (LONG)x - 1;
	rt.top = (LONG)y - 1;
	rt.right = (LONG)x + 1;
	rt.bottom = (LONG)y + 1;

	/* �u���V�̍쐬 */
	hBrush = CreateSolidBrush(RGB(col, col, col));
	hOldBrush = SelectObject(hdc, hBrush);

	/* �l�p�`�̕`�� */
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

	rlen = 300 / 2;   // ���̔��a
	min = -rlen;
	max = rlen;

	/* �@���x�N�g�����v�Z���� */
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

			/* ���̗ʂ��v�Z���� */
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

// �E�B���h�E�v���V�[�W��
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

// ���C���֐�
int WINAPI WinMain(
  HINSTANCE hInstance,      // ���݂̃C���X�^���X�̃n���h��
  HINSTANCE hPrevInstance,  // �ȑO�̃C���X�^���X�̃n���h��
  LPSTR lpCmdLine,          // �R�}���h���C��
  int nCmdShow              // �\�����
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
    RegisterClassEx(&wc);  // �E�B���h�E�N���X�̓o�^

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
    ShowWindow(hWnd, nCmdShow);   // �E�B���h�E�̕`��
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // ���b�Z�[�W���[�v
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


