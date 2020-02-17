/* 2003/7/13
 *
 * linux_thread.c - �u�bLinux�U���h��������d�ҵ{���v�ץ���
 *
 * [how to compile]
 * # gcc -lpthread linux_thread.c
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TH_MAX 5    /* �Ұʪ�������� */
#define MAX 10      /* �}�C�� */

int g_value[MAX];    /* ����������@�P�֦����}�C��� */
int g_count[TH_MAX]; /* �C�Ӱ�������}�l�ȸ�� */

pthread_mutex_t lock;  /* mutex���� */


/* ����� routine */
void *thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	pthread_mutex_lock(&lock);  /* mutex��w */

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	sleep(10);

	pthread_mutex_unlock(&lock); /* mutex���� */

	pthread_exit(0);  /* ���ܰ�������� */
	return NULL;
}


/* main��� */
int main(void)
{
	pthread_attr_t attr;
	struct sched_param param;
	pthread_t hd[TH_MAX];   /* ����� ID */
	int i, num, err;

	pthread_mutex_init(&lock, NULL);  /* mutex���󪺪�l�� */

	/* thread attribute setting */
	pthread_attr_init(&attr);    /* default */
	bzero(&param, sizeof(param));
	param.__sched_priority = 0;  /* priority */
	pthread_attr_setschedparam(&attr, &param);

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		/* ����������� */
		err = pthread_create(&hd[i], &attr, thread_func, &g_count[i]);
		if (err != 0) {  /* ��������ͥ��� */
			printf("err %d\n", err);
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* ���ݨϥΤ������������ */
		for (i = 0 ; i < num ; i++) {
			pthread_join(hd[i], NULL);
		}
	}

	pthread_mutex_destroy(&lock); /* ����������Хܤ� */

	return 0;
}


