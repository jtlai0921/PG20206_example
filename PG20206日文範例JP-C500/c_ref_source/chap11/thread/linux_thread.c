/* 2003/7/13
 *
 * linux_thread.c - 「Linuxにおけるマルチスレッドのサンプルコード」修正版
 *
 * [how to compile]
 * # gcc -lpthread linux_thread.c
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TH_MAX 5    /* スレッドを起こす数 */
#define MAX 10      /* 配列数 */

int g_value[MAX];    /* スレッド間で共有される配列データ */
int g_count[TH_MAX]; /* スレッド毎の開始値データ */

pthread_mutex_t lock;  /* mutexオブジェクト */


/* スレッドルーチン */
void *thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	pthread_mutex_lock(&lock);  /* mutexロック */

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	sleep(10);

	pthread_mutex_unlock(&lock); /* mutアンロック */

	pthread_exit(0);  /* スレッド終了指示 */
	return NULL;
}


/* メイン関数 */
int main(void)
{
	pthread_attr_t attr;
	struct sched_param param;
	pthread_t hd[TH_MAX];   /* スレッドID */
	int i, num, err;

	pthread_mutex_init(&lock, NULL);  /* mutexオブジェクトの初期化 */

	/* thread attribute setting */
	pthread_attr_init(&attr);    /* default */
	bzero(&param, sizeof(param));
	param.__sched_priority = 0;  /* priority */
	pthread_attr_setschedparam(&attr, &param);

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		/* スレッドの生成 */
		err = pthread_create(&hd[i], &attr, thread_func, &g_count[i]);
		if (err != 0) {  /* スレッド生成失敗 */
			printf("err %d\n", err);
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* スレッドの終了を待ち合わせる */
		for (i = 0 ; i < num ; i++) {
			pthread_join(hd[i], NULL);
		}
	}

	pthread_mutex_destroy(&lock); /* mutexオブジェクトの解放 */

	return 0;
}


