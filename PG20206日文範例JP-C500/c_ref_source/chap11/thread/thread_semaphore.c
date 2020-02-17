/* 2003/7/12
 *
 * thread_semaphore.c 
 * �u�r��������g�����}���`�X���b�h�v���O�����v
 *
 */

#include <windows.h>
#include <process.h>
#include <stdio.h>

#define TH_MAX 5    /* �X���b�h���N������ */
#define MAX 10      /* �z�� */

int g_value[MAX];    /* �X���b�h�Ԃŋ��L�����z��f�[�^ */
int g_count[TH_MAX]; /* �X���b�h���̊J�n�l�f�[�^ */


/*
 * �r������
 */
HANDLE lock;   /* ���b�N�p�ϐ��i�Z�}�t�H�I�u�W�F�N�g�j */
#define INIT_LOCK() {lock = CreateSemaphore(NULL, 1, 1, NULL);} 
#define FINAL_LOCK() CloseHandle(lock)
#define SPIN_LOCK() WaitForSingleObject(lock, INFINITE)
#define SPIN_UNLOCK() ReleaseSemaphore(lock, 1, NULL)


/* �X���b�h���[�`�� */
unsigned __stdcall thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	SPIN_LOCK();

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
		Sleep(1);  /* context switch���N���₷���悤�� */
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	SPIN_UNLOCK();

	_endthreadex(0);
	return 0;
}


/* ���C���֐� */
int main(void)
{
	HANDLE hd[TH_MAX];   /* �X���b�h�n���h�� */
	unsigned tid;        /* �X���b�hID */
	int i, num;

	INIT_LOCK();

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		hd[i] = (HANDLE)_beginthreadex(NULL, 0, thread_func, &g_count[i], 0, &tid);
		if (hd[i] == 0) {  /* �X���b�h�������s */
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* �d�|���蒆�̃X���b�h�̏I����҂����킹�� */
		WaitForMultipleObjects(num, hd, TRUE, INFINITE);

		/* �X���b�h�n���h������� */
		for (i = 0 ; i < num ; i++) {
			CloseHandle(hd[i]);
		}
	}

	FINAL_LOCK();

	return 0;
}


