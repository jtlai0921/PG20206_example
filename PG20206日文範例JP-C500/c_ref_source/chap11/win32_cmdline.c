/*
 * Windows�v���O�����ł̃R�}���h���C�������̎󂯎��
 *
 * for compile:
 *  >cl win32_cmdline.c user32.lib kernel32.lib
 */
#include <windows.h>
#include <stdlib.h>

// ���C���֐�
int WINAPI WinMain(
  HINSTANCE hInstance,      // ���݂̃C���X�^���X�̃n���h��
  HINSTANCE hPrevInstance,  // �ȑO�̃C���X�^���X�̃n���h��
  LPSTR lpCmdLine,          // �R�}���h���C��
  int nCmdShow              // �\�����
) 
{
	LPTSTR str;
	char buf[256];

	MessageBox(NULL, lpCmdLine, "WinMain�̈���", MB_OK);

	str = GetCommandLine();
	MessageBox(NULL, str, "GetCommandLine()", MB_OK);

	sprintf(buf, "argc=%d\r\nargv=%s %s %s\n", 
			__argc, __argv[0], __argv[1], __argv[2]);
	MessageBox(NULL, buf, "__argc & __argv", MB_OK);

	return 0;
}

