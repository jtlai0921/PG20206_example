/* 2003/7/26
 *
 * itimer.c - [Interval Timer sample program]
 *
 */
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>


void signal_handler(int num)
{
	printf("Accept signal!\n");
}

int main()
{
	struct itimerval tick;

	/* prohibit CTRL+C */
	signal(SIGINT, SIG_IGN);

	printf("Set signal handler\n");
	signal(SIGALRM, signal_handler);

	printf("Set interval timer\n");
	memset(&tick, 0, sizeof(tick));
	tick.it_value.tv_sec = 10;
	tick.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &tick, NULL);

	printf("Sleeping...\n");
	pause();

	printf("Wakeup!\n");

	return 0;
}

