/* 2003/7/13
 *
 * linux_thread.c - ��Linux�ˤ�����ޥ������åɤΥ���ץ륳���ɡ׽�����
 *
 * [how to compile]
 * # gcc -lpthread linux_thread.c
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define TH_MAX 5    /* ����åɤ򵯤����� */
#define MAX 10      /* ����� */

int g_value[MAX];    /* ����åɴ֤Ƕ�ͭ���������ǡ��� */
int g_count[TH_MAX]; /* ����å���γ����ͥǡ��� */

pthread_mutex_t lock;  /* mutex���֥������� */


/* ����åɥ롼���� */
void *thread_func(void *arg)
{
	int i, j, k;
	int argv = *(int *)arg;

	pthread_mutex_lock(&lock);  /* mutex��å� */

	for (i = 0 ; i < MAX ; i++) {
		g_value[i] = argv + i;
	}

	for (i = 0 ; i < MAX ; i++) {
		printf("[%d]=%-2d ", i, g_value[i]);
	}
	printf("\n");

	sleep(10);

	pthread_mutex_unlock(&lock); /* mut�����å� */

	pthread_exit(0);  /* ����åɽ�λ�ؼ� */
	return NULL;
}


/* �ᥤ��ؿ� */
int main(void)
{
	pthread_attr_t attr;
	struct sched_param param;
	pthread_t hd[TH_MAX];   /* ����å�ID */
	int i, num, err;

	pthread_mutex_init(&lock, NULL);  /* mutex���֥������Ȥν���� */

	/* thread attribute setting */
	pthread_attr_init(&attr);    /* default */
	bzero(&param, sizeof(param));
	param.__sched_priority = 0;  /* priority */
	pthread_attr_setschedparam(&attr, &param);

	num = TH_MAX;
	for (i = 0 ; i < TH_MAX ; i++) {
		g_count[i] = i;

		/* ����åɤ����� */
		err = pthread_create(&hd[i], &attr, thread_func, &g_count[i]);
		if (err != 0) {  /* ����å��������� */
			printf("err %d\n", err);
			num = i;
			goto error;
		}
	}

error:;
	if (num > 0) {
		/* ����åɤν�λ���Ԥ���碌�� */
		for (i = 0 ; i < num ; i++) {
			pthread_join(hd[i], NULL);
		}
	}

	pthread_mutex_destroy(&lock); /* mutex���֥������Ȥβ��� */

	return 0;
}


