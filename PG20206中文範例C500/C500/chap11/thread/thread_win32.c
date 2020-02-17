/*
 * �ϥ�Win32 API�ӹ�{�h�����
 *
 * for compile:
 *  >cl thread_win32.c user32.lib kernel32.lib
 */
#include <windows.h>

int count = 0;

// ��������
void do_handler(DWORD val)
{
	count += val;
	Sleep(3000);
}

// main���
int WINAPI WinMain(
  HINSTANCE hInstance,      //�{�b����(instance)���Хܤ�
  HINSTANCE hPrevInstance,  //�H�e����(instance)���Хܤ�
  LPSTR lpCmdLine,          //�R�O�C
  int nCmdShow              //��ܪ��A
) 
{
	HANDLE hd;
	DWORD tid;
	int val = 333;
	char buf[256];

	hd = CreateThread(
			NULL, 
			0,
			(LPTHREAD_START_ROUTINE)do_handler,
			(LPVOID)val,
			0,
			&tid
			);


	if (hd == NULL) {
		MessageBox(NULL, "��������ͥ���", "���~", 
			MB_OK | MB_ICONEXCLAMATION);

	} else {
		WaitForSingleObject(hd, INFINITE);
	}

	sprintf(buf, "count=%d", count);
	MessageBox(NULL, buf, "���G", MB_OK);

	return 0;
}

