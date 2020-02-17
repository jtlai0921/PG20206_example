/*
 * Windows程式中接收命令列引數
 *
 * for compile:
 *  >cl win32_cmdline.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <stdlib.h>

// main函數
int WINAPI WinMain(
  HINSTANCE hInstance,      //現在的實體標示元
  HINSTANCE hPrevInstance,  //以前的實體標示元
  LPSTR lpCmdLine,          //命令列
  int nCmdShow              //顯示狀態
) 
{
	LPTSTR str;
	char buf[256];

	MessageBox(NULL, lpCmdLine, "WinMain的引數", MB_OK);

	str = GetCommandLine();
	MessageBox(NULL, str, "GetCommandLine()", MB_OK);

	sprintf(buf, "argc=%d\r\nargv=%s %s %s\n", 
			__argc, __argv[0], __argv[1], __argv[2]);
	MessageBox(NULL, buf, "__argc & __argv", MB_OK);

	return 0;
}

