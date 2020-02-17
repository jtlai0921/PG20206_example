/*
 * 總之試著繪出視窗
 *
 * for compile:
 * >cl /W3 /nologo step1.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
 *
 * Copyright (C)2003 YUTAKA
 * All rights reserved.
 */
#include <windows.h>

#define MYWNDCLASS  "MYWNDCLASS"
#define CAPTION     "繪出視窗"

#define WIDTH 320
#define HEIGHT 320

// 視窗程序
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

// WinMain函數
int WINAPI WinMain(
  HINSTANCE hInstance,      // 現在實體的標示元
  HINSTANCE hPrevInstance,  // 以前實體的標示元
  LPSTR lpCmdLine,          // 命令列
  int nCmdShow              // 顯示狀態
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
    RegisterClassEx(&wc);  // 登錄視窗類別

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
    ShowWindow(hWnd, nCmdShow);   // 描繪視窗
	UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0)) { // 訊息迴圈
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


