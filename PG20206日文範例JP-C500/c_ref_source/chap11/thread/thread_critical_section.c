/* 2003/7/12
 *
 * thread_critical_section.c 
 * 「排他制御を使ったマルチスレッドプログラム」
 *
 * [コンパイル方法]
 *   >cl /MT /nologo thread_critical_section.c  (for VC++)
 *   >bcc32 -tWM thread_critical_section.c      (for BCC++)
 *
 */

#include <windows.h>
#include <process.h>
#include <stdio.h>

#define TH_MAX 5    /* スレッドを起こす数 */
#define MAX 10      /* 配列数 */

int g_value[MAX];    /* スレッド間で共有される配列データ */
int g_count[TH_MAX]; /* スレッド毎の開始値データ */


/*
 * 排他制御
 */
CRITICAL_SECTION lock;   /* ロック用変数 */
#define INIT_LOCK() InitializeCriticalSection(&lock)  /* クリティカルセクションオブジェクトの初期化 */
#define FINAL_LOCK() DeleteCriticalSection(&lock)  /* クリティカルセクションオブジェクトの解放 */
#define SPIN_LOCK() EnterCriticalSection(&lock)  /* ロック取得 */
#define SPIN_UNLOCK() LeaveCriticalSection(&lock)  /* ロック解放 */


/* スレッドルーチン */
unsigned __stdcall thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	SPIN_LOCK();

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
		Sleep(1);  /* context switchが起きやすいように */
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	SPIN_UNLOCK();

	_endthreadex(0);
	return 0;
}


/* メイン関数 */
int main(void)
{
	HANDLE hd[TH_MAX];   /* スレッドハンドル */
	unsigned tid;        /* スレッドID */
	int i, num;

	INIT_LOCK();

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		hd[i] = (HANDLE)_beginthreadex(NULL, 0, thread_func, &g_count[i], 0, &tid);
		if (hd[i] == 0) {  /* スレッド生成失敗 */
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* 仕掛かり中のスレッドの終了を待ち合わせる */
		WaitForMultipleObjects(num, hd, TRUE, INFINITE);

		/* スレッドハンドルを閉じる */
		for (i = 0 ; i < num ; i++) {
			CloseHandle(hd[i]);
		}
	}

	FINAL_LOCK();

	return 0;
}


