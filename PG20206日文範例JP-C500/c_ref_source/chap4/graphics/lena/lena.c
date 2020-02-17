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
#define CAPTION     "�r�b�g�}�b�v�摜�̓ǂݍ���"

#define WIDTH 320
#define HEIGHT 320


// BMP�摜�����[�h����
void load_lena_image(HWND hWnd, HDC hdc)
{
	HDC hmdc;
	HBITMAP hBitmap;
	BITMAP bmp;
	HINSTANCE hInst;
	int bmp_w, bmp_h;


	// �C���X�^���X�̃n���h��
	hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// ���\�[�X����r�b�g�}�b�v�摜�����[�h
	hBitmap =
		LoadImage(hInst, MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0,
				  LR_DEFAULTCOLOR);
	if (hBitmap == NULL) {
		char buf[128];
		sprintf(buf, "%d", GetLastError());
		MessageBox(hWnd, buf, "ERROR", MB_OK);
		return;
	}

	// �摜�̉��Əc�̃T�C�Y���擾����
	GetObject(hBitmap, sizeof(BITMAP), &bmp);
	bmp_w = (int) bmp.bmWidth;
	bmp_h = (int) bmp.bmHeight;

	// �������f�o�C�X�R���e�L�X�g�̍쐬
	hmdc = CreateCompatibleDC(hdc);
	// �������f�o�C�X�R���e�L�X�g�ƃr�b�g�}�b�v�摜���o�C���h����
	SelectObject(hmdc, hBitmap);

	// �r�b�g�}�b�v�摜���X�N���[���֕`�悷��
	BitBlt(hdc, 0, 0, bmp_w, bmp_h, hmdc, 0, 0, SRCCOPY);	

	// �s�v�ȃ��\�[�X���������
	DeleteDC(hmdc);
	DeleteObject(hBitmap);
}

// �E�B���h�E�v���V�[�W��
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
	ShowWindow(hWnd, nCmdShow);	// �E�B���h�E�̕`��
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {	// ���b�Z�[�W���[�v
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

