/*
 * Windows�{���������R�O�C�޼�
 *
 * for compile:
 *  >cl win32_cmdline.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <stdlib.h>

// main���
int WINAPI WinMain(
  HINSTANCE hInstance,      //�{�b������Хܤ�
  HINSTANCE hPrevInstance,  //�H�e������Хܤ�
  LPSTR lpCmdLine,          //�R�O�C
  int nCmdShow              //��ܪ��A
) 
{
	LPTSTR str;
	char buf[256];

	MessageBox(NULL, lpCmdLine, "WinMain���޼�", MB_OK);

	str = GetCommandLine();
	MessageBox(NULL, str, "GetCommandLine()", MB_OK);

	sprintf(buf, "argc=%d\r\nargv=%s %s %s\n", 
			__argc, __argv[0], __argv[1], __argv[2]);
	MessageBox(NULL, buf, "__argc & __argv", MB_OK);

	return 0;
}

