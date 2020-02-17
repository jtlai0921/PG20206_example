/*
 * Windowsプログラムでのコマンドライン引数の受け取り
 *
 * for compile:
 *  >cl win32_cmdline.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <stdlib.h>

// メイン関数
int WINAPI WinMain(
  HINSTANCE hInstance,      // 現在のインスタンスのハンドル
  HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
  LPSTR lpCmdLine,          // コマンドライン
  int nCmdShow              // 表示状態
) 
{
	LPTSTR str;
	char buf[256];

	MessageBox(NULL, lpCmdLine, "WinMainの引数", MB_OK);

	str = GetCommandLine();
	MessageBox(NULL, str, "GetCommandLine()", MB_OK);

	sprintf(buf, "argc=%d\r\nargv=%s %s %s\n", 
			__argc, __argv[0], __argv[1], __argv[2]);
	MessageBox(NULL, buf, "__argc & __argv", MB_OK);

	return 0;
}

