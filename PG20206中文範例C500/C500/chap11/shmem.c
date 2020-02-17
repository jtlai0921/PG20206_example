/*
 * shmem.c
 *
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

char *shm_ptr;

int main(void)
{
	pid_t pid;
	int status, i;
	int shmid;

	/* assign shared memory segment */
	shmid = shmget(IPC_PRIVATE, 2048, IPC_CREAT | 0666);
	if (shmid == -1) {
		perror("shmget() error");
		exit(1);
	}

	/* attach shared memory */
	shm_ptr = shmat(shmid, NULL, 0);
	if (shm_ptr == (char *)-1) {
		perror("shmat() error");
		exit(1);
	}

	pid = fork();
	if (pid == 0) {  /* child process */
		for (i = 0 ; i < 100 ; i++) {
			shm_ptr[i] = 'C';
			usleep(200);
		}
		/*
		if (shmdt(shm_ptr) == -1) {
			printf("fork(): shmdt() error\n"); exit(1);
		}*/
		exit(1);
	}

	/* following code is parent process */
	for (i = 0 ; i < 100 ; i++) {
		shm_ptr[i] = 'P';
		usleep(10);
	}

	wait(&status);

	for (i = 0 ; i < 100 ; i++) {
		printf("%c", shm_ptr[i]);
	}
	printf("\n");

	/* deatch shared memory */
	if (shmdt(shm_ptr) == -1) {
		printf("shmdt() error\n"); exit(1);
	}

	/* remove shared memory segment */
	if (shmctl(shmid, IPC_RMID, 0) == -1) {
		printf("shmctl() error\n"); exit(1);
	}

	return 0;
}


