/* 2003/7/12
 *
 * thread_critical_section.c 
 * �u�ϥΤ������h������{���v
 *
 * [�sĶ��k]
 *   >cl /MT /nologo thread_critical_section.c  (for VC++)
 *   >bcc32 -tWM thread_critical_section.c      (for BCC++)
 *
 */

#include <windows.h>
#include <process.h>
#include <stdio.h>

#define TH_MAX 5    /* �Ұʪ�������� */
#define MAX 10      /* �}�C�� */

int g_value[MAX];    /* ����������@�P�֦����}�C��� */
int g_count[TH_MAX]; /* �C�Ӱ�������}�l�ȸ�� */


/*
 * ����
 */
CRITICAL_SECTION lock;   /* ��w�Ϊ��ܼ� */
#define INIT_LOCK() InitializeCriticalSection(&lock)  /* ����Ϭq���󪺪�l�� */
#define FINAL_LOCK() DeleteCriticalSection(&lock)  /* ��������Ϭq���� */
#define SPIN_LOCK() EnterCriticalSection(&lock)  /* ���o��w */
#define SPIN_UNLOCK() LeaveCriticalSection(&lock)  /* �Ѱ���w */


/* ����� routine */
unsigned __stdcall thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	SPIN_LOCK();

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
		Sleep(1);  /* ���F��context switch�e���o�� */
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	SPIN_UNLOCK();

	_endthreadex(0);
	return 0;
}


/* main��� */
int main(void)
{
	HANDLE hd[TH_MAX];   /* ������Хܤ� */
	unsigned tid;        /* ����� ID */
	int i, num;

	INIT_LOCK();

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		hd[i] = (HANDLE)_beginthreadex(NULL, 0, thread_func, &g_count[i], 0, &tid);
		if (hd[i] == 0) {  /* ��������ͥ��� */
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* ���ݨϥΤ������������ */
		WaitForMultipleObjects(num, hd, TRUE, INFINITE);

		/* ����������Хܤ� */
		for (i = 0 ; i < num ; i++) {
			CloseHandle(hd[i]);
		}
	}

	FINAL_LOCK();

	return 0;
}


