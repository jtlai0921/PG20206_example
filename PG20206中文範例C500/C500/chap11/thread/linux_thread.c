/* 2003/7/13
 *
 * linux_thread.c - 「在Linux下的多執行緒的範例程式」修正版
 *
 * [how to compile]
 * # gcc -lpthread linux_thread.c
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TH_MAX 5    /* 啟動的執行緒數 */
#define MAX 10      /* 陣列數 */

int g_value[MAX];    /* 執行緒之間共同擁有的陣列資料 */
int g_count[TH_MAX]; /* 每個執行緒的開始值資料 */

pthread_mutex_t lock;  /* mutex物件 */


/* 執行緒 routine */
void *thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	pthread_mutex_lock(&lock);  /* mutex鎖定 */

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	sleep(10);

	pthread_mutex_unlock(&lock); /* mutex解鎖 */

	pthread_exit(0);  /* 指示執行緒結束 */
	return NULL;
}


/* main函數 */
int main(void)
{
	pthread_attr_t attr;
	struct sched_param param;
	pthread_t hd[TH_MAX];   /* 執行緒 ID */
	int i, num, err;

	pthread_mutex_init(&lock, NULL);  /* mutex物件的初始化 */

	/* thread attribute setting */
	pthread_attr_init(&attr);    /* default */
	bzero(&param, sizeof(param));
	param.__sched_priority = 0;  /* priority */
	pthread_attr_setschedparam(&attr, &param);

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		/* 執行緒的產生 */
		err = pthread_create(&hd[i], &attr, thread_func, &g_count[i]);
		if (err != 0) {  /* 執行緒產生失敗 */
			printf("err %d\n", err);
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* 等待使用中的執行緒結束 */
		for (i = 0 ; i < num ; i++) {
			pthread_join(hd[i], NULL);
		}
	}

	pthread_mutex_destroy(&lock); /* 關閉執行緒標示元 */

	return 0;
}


