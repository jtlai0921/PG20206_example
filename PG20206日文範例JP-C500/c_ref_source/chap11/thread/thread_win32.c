/*
 * Win32 API���g���ă}���`�X���b�h����������
 *
 * for compile:
 *  >cl thread_win32.c user32.lib kernel32.lib
 */
#include <windows.h>

int count = 0;

// �X���b�h�֐�
void do_handler(DWORD val)
{
	count += val;
	Sleep(3000);
}

// ���C���֐�
int WINAPI WinMain(
  HINSTANCE hInstance,      // ���݂̃C���X�^���X�̃n���h��
  HINSTANCE hPrevInstance,  // �ȑO�̃C���X�^���X�̃n���h��
  LPSTR lpCmdLine,          // �R�}���h���C��
  int nCmdShow              // �\�����
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
		MessageBox(NULL, "�X���b�h�������ł��܂���ł���", "�G���[", 
			MB_OK | MB_ICONEXCLAMATION);

	} else {
		WaitForSingleObject(hd, INFINITE);
	}

	sprintf(buf, "count=%d", count);
	MessageBox(NULL, buf, "����", MB_OK);

	return 0;
}

