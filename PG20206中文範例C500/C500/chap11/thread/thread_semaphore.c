/* 2003/7/12
 *
 * thread_semaphore.c 
 * 「使用互斥的多執行緒程式」
 *
 */

#include <windows.h>
#include <process.h>
#include <stdio.h>

#define TH_MAX 5    /* 啟動的執行緒數 */
#define MAX 10      /* 陣列數 */

int g_value[MAX];    /* 執行緒之間共同擁有的陣列資料 */
int g_count[TH_MAX]; /* 每個執行緒的開始值資料 */


/*
 * 互斥
 */
HANDLE lock;   /* 鎖定用的變數(信號機物件) */
#define INIT_LOCK() {lock = CreateSemaphore(NULL, 1, 1, NULL);} 
#define FINAL_LOCK() CloseHandle(lock)
#define SPIN_LOCK() WaitForSingleObject(lock, INFINITE)
#define SPIN_UNLOCK() ReleaseSemaphore(lock, 1, NULL)


/* 執行緒 routine */
unsigned __stdcall thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	SPIN_LOCK();

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
		Sleep(1);  /* 為了讓context switch容易發生 */
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	SPIN_UNLOCK();

	_endthreadex(0);
	return 0;
}


/* main函數 */
int main(void)
{
	HANDLE hd[TH_MAX];   /* 執行緒標示元 */
	unsigned tid;        /* 執行緒ID */
	int i, num;

	INIT_LOCK();

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		hd[i] = (HANDLE)_beginthreadex(NULL, 0, thread_func, &g_count[i], 0, &tid);
		if (hd[i] == 0) {  /* 執行緒產生失敗 */
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* 等待使用中的執行緒結束 */
		WaitForMultipleObjects(num, hd, TRUE, INFINITE);

		/* 關閉執行緒標示元 */
		for (i = 0 ; i < num ; i++) {
			CloseHandle(hd[i]);
		}
	}

	FINAL_LOCK();

	return 0;
}


