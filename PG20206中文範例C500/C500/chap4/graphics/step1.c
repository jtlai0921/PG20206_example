/*
 * �`���յ�ø�X����
 *
 * for compile:
 * >cl /W3 /nologo step1.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "ø�X����"

#define WIDTH 320
#define HEIGHT 320

// �����{��
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

// WinMain���
int WINAPI WinMain(
  HINSTANCE hInstance,      // �{�b���骺�Хܤ�
  HINSTANCE hPrevInstance,  // �H�e���骺�Хܤ�
  LPSTR lpCmdLine,          // �R�O�C
  int nCmdShow              // ��ܪ��A
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
    RegisterClassEx(&wc);  // �n���������O

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
    ShowWindow(hWnd, nCmdShow);   // �yø����
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // �T���j��
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


