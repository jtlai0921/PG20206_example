/*
 * superball
 *
 * for compile:
 *  >cl /O2 /nologo superball.c user32.lib kernel32.lib gdi32.lib /link /subsystem:windows
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
#define CAPTION     "superball"

#define ID_TIMER 32767
#define TIMEOUT 100

#define WIDTH 480
#define HEIGHT 480

#define MAX 3
typedef struct {
	int x;
	int y;
	int r;
	double cos_ang;
	double sin_ang;
} point_t;

point_t balls[MAX];

double angle;


#define PI 3.141592
#define PALMAX 256

DWORD palette[PALMAX];
DWORD dwStartTime;
HDC memDC;
HWND hWndMain;

#define POS(x,y) ((x) + (y)*WIDTH)
int depth[WIDTH * HEIGHT];


void add_depth(int x, int y, int col)
{
	int val;
	 
	val = depth[POS(x,y)];
	if (val == 0) {
		val += col;
	} else {
		//val += ((col) > 64 ? (col)-64 : 0);
		val += col/2;
	}
	depth[POS(x,y)] = val;
}


int get_depth_col(int x, int y)
{
	int val;

	val = depth[POS(x-1,y-1)];
	if (val > 255)
		return (255);

	val = depth[POS(x-1,y)];
	if (val > 255)
		return (255);

	val = depth[POS(x,y-1)];
	if (val > 255)
		return (255);

	val = depth[POS(x,y)];
	if (val > 255)
		return (255);

	return (val);
}


/*¦bµe­±¤WµeÂI*/
void draw_dot_point(HWND hWnd, HDC hdc, int x, int y, int col) 
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;
	int r, g, b;
	int val;

	/*²¾°Ê¨ìµe­±¤¤¤ß */
	x += WIDTH / 2;
	y += HEIGHT / 2;

	rt.left = (LONG)x - 1;
	rt.top = (LONG)y - 1;
	rt.right = (LONG)x + 1;
	rt.bottom = (LONG)y + 1;

	add_depth(x-1,y-1, col);
	add_depth(x-1,y  , col);
	add_depth(x  ,y-1, col);
	add_depth(x  ,y  , col);

	val = get_depth_col(x, y);

	/*²£¥Íµ§¨ê*/
	hBrush = CreateSolidBrush(palette[val]);
	hOldBrush = SelectObject(hdc, hBrush);

	/* Ã¸¥X¥|¤è§Î */
	FillRect(hdc, &rt, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);
}

void clear_screen(HWND hWnd, HDC hdc)
{
    RECT rt;
	HBRUSH hBrush, hOldBrush;
	int i;

	rt.left = 0;
	rt.top = 0;
	rt.right = WIDTH;
	rt.bottom = HEIGHT;

	/*²£¥Íµ§¨ê*/
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	hOldBrush = SelectObject(hdc, hBrush);

	/*Ã¸¥X¥|¤è§Î*/
	FillRect(hdc, &rt, hBrush);

    SelectObject(hdc, hOldBrush);
    DeleteObject(hBrush);

	ZeroMemory(depth, sizeof(depth));
}

void draw_ball(HWND hWnd, HDC hdc, int px, int py) 
{
	int rlen, col;
	int cx, cy, x, y;
	int min, max;
	double val, z;

	rlen = 50;
	min = -rlen;
	max = rlen;

	for (cy = min ; cy < max ; cy += 2) {
		for (cx = min ; cx < max ; cx += 2) {
			x = cx;
			y = cy;

			val = rlen*rlen - x*x - y*y;
			if (val < 0)
				continue;

			z = sqrt(val);
			col = z * 3;

			if (col > 255)
				col = 255;
			if (col < 0)
				col = 0;

			printf("x %f y %f z %f -> col %d\n", x, y, z, col);

			draw_dot_point(hWnd, hdc, x + px, y + py, col);
		}
	}
}

void do_graphics(HWND hWnd, HDC hdc) 
{
	int i;

	clear_screen(hWnd, hdc);

	angle += 4;
	if (angle >= 360)
		angle = 0;

	for (i = 0 ; i < MAX ; i++) {
		balls[i].x = balls[i].r * cos(balls[i].cos_ang * angle * PI/180);
		balls[i].y = balls[i].r * sin(balls[i].sin_ang * angle * PI/180);

		draw_ball(hWnd, hdc, balls[i].x, balls[i].y);
	}
}

void init_graphics(void)
{
	int i;
	HDC hdc;
	HBITMAP hMem;

	for (i = 0 ; i < MAX ; i++) {
		balls[i].x = WIDTH / 2;
		balls[i].y = HEIGHT / 2;
		balls[i].r = WIDTH / (4 + i);
		balls[i].cos_ang = i*2 + 1;
		balls[i].sin_ang = i*2 + 2;
	}
	angle = 0.0;

	for (i = 0 ; i < 64 ; i++) {
		palette[i] = RGB(0, 0, 4*i);
	}
	for (i = 64 ; i < 128 ; i++) {
		palette[i] = RGB(4*i, 4*i, 255);
	}
	for (i = 128 ; i < PALMAX ; i++) {
		palette[i] = RGB(255, 255, 255);
	}

	dwStartTime = GetTickCount();

	// »s§@Âù­«½w½Ä°Ï
	hdc = GetDC(hWndMain);
	memDC = CreateCompatibleDC(hdc);
	hMem = CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
	SelectObject(memDC, hMem);
	DeleteObject(hMem);
	ReleaseDC(hWndMain, hdc);
}


void do_effect(void)
{
	DWORD fps, now;
	RECT rect = {0, 0, WIDTH, HEIGHT};
	char buf[128];

	// ­pºâ¯S®Ä
	now = GetTickCount();
	if (now - dwStartTime <= 0)
		fps = 1000;
	else
		fps = 1000 / (now - dwStartTime);
	dwStartTime = now;
	wsprintf(buf, "%d FPS", fps);

	do_graphics(hWndMain, memDC);
	DrawText(memDC, buf, -1, &rect, DT_LEFT);
	InvalidateRect(hWndMain, NULL, FALSE);
}


// µøµ¡µ{§Ç
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBITMAP hMem;
	DWORD fps;
	RECT rect = {0, 0, WIDTH, HEIGHT};
	char buf[128];

    switch (uMsg) {
	case WM_CREATE:

#if 0
		if (SetTimer(hWnd, ID_TIMER, TIMEOUT, NULL) == 0) {
			MessageBox(hWnd, "ERROR", "SetTimer()‚ªŽ¸”s", MB_OK);
		}
#endif
		break;

	case WM_TIMER:
#if 0
		// ­pºâ¯S®Ä
		fps = 1000 / (GetTickCount() - dwStartTime);
		dwStartTime = GetTickCount();
		wsprintf(buf, "%d FPS", fps);

		KillTimer(hWnd, ID_TIMER);
		do_graphics(hWnd, memDC);
		DrawText(memDC, buf, -1, &rect, DT_RIGHT);
		InvalidateRect(hWnd, NULL, FALSE);
#endif
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, memDC,  0, 0, SRCCOPY);  
		EndPaint(hWnd, &ps);
#if 0
		SetTimer(hWnd, ID_TIMER, TIMEOUT, NULL);
#endif
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

//WinMain¨ç¼Æ
int WINAPI WinMain(
  HINSTANCE hInstance,      // ²{¦b¹êÅéªº¼Ð¥Ü¤¸
  HINSTANCE hPrevInstance,  // ¥H«e¹êÅéªº¼Ð¥Ü¤¸
  LPSTR lpCmdLine,          // ©R¥O¦C
  int nCmdShow              // Åã¥Üª¬ºA
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
    //wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
//    wc.hbrBackground    =  GetStockObject(WHITE_BRUSH);
    wc.hbrBackground    =  GetStockObject(BLACK_BRUSH);
    wc.lpszClassName    = MYWNDCLASS;
    RegisterClassEx(&wc);  // µn¿ýµøµ¡Ãþ§O

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

	hWndMain = hWnd;
	init_graphics();

    ShowWindow(hWnd, nCmdShow);   // ´yÃ¸µøµ¡
	UpdateWindow(hWnd);

	for (;;) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == 0) { // °T®§°j°é
			do_effect();

		} else {
			if (GetMessage(&msg, NULL, 0, 0) == 0) { 
				return msg.wParam;
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		Sleep(1);  /* °±¤î1¬í */
	}

#if 0
    while (GetMessage(&msg, NULL, 0, 0)) { // °T®§°j°é
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
#endif

    return msg.wParam;
}


