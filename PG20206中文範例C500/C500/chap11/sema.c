/*
 * sema.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/sem.h> 
#include <sys/wait.h>


#ifdef SEMAPHORE

void up(int semid)
{
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = 1;  /* V operation */
	sops.sem_flg = SEM_UNDO;  

	if (semop(semid, &sops, 1) != 0) {
		perror("semaphore V operation error\n");
		exit(1);
	}
}

void down(int semid)
{
	struct sembuf sops;

	sops.sem_num = 0;
	sops.sem_op = -1;  /* P operation */
	sops.sem_flg = SEM_UNDO; 

	if (semop(semid, &sops, 1) != 0) {
		perror("semaphore P operation error\n");
		exit(1);
	}
}

#else

void up(int dummy) { }

void down(int dummy) { }

#endif


int main(void)
{
	int i;
	int semid;
	union senum 
	{  
		int val;
		struct semid_ds *buf;
		ushort *array;
		struct seminfo *__buf;
	} arg;


	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
	if (semid == -1) {
		perror("semget() error");
		exit(1);
	}
	arg.val = 1;
	if (semctl(semid, 0, SETVAL, arg) == -1) {
		perror("semctl() error\n"); exit(1);
	}


	if (fork() == 0) {  /* child process */
		down(semid);
		//
		// critical section
		//
		for (i = 0 ; i < 30 ; i++) {
			printf("C");
			fflush(stdout);
			usleep(100);
			//sleep(rand() %2);
		}
		printf("\n");
		up(semid);
		exit(1);
	}

	/* following code is parent process */
	down(semid);
	//
	// critical section
	//
	for (i = 0 ; i < 30 ; i++) {
		printf("P"); 
		fflush(stdout);
		usleep(10);
		//sleep(rand() %2);
	}
	printf("\n");
	up(semid);

	wait(NULL);

	/* remove semaphore ID */
	if (semctl(semid, 0, IPC_RMID) == -1) {
		perror("semctl() error\n"); exit(1);
	}

	return 0;
}

