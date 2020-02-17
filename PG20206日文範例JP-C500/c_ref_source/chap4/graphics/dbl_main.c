/*
 * WinMain() �� main() �̍���
 *
 * for compile:
 * >cl /W3 /nologo dbl_main.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
 * >cl /W3 /nologo dbl_main.c user32.lib kernel32.lib gdi32.lib /link /subsystem:console
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>
#include <stdio.h>

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "�}�`��`��"

#define WIDTH 320
#define HEIGHT 320

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH hBrush, hBrushPrev;

    switch (uMsg) {
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(20, 20, 255));
		hBrushPrev = SelectObject(hdc, hBrush);

		Ellipse(hdc, 10, 10, 100, 100);
		Rectangle(hdc, 100, 100, 200, 200);

		SelectObject(hdc, hBrushPrev);
		DeleteObject(hBrush);
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
	printf("hello, world\n");

	return 0;
}



