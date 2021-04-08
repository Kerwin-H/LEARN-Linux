#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/shm.h>

#define IPC_KEY 0x12345678

int main(int argc, char *argv[]){

	int shmid = shmget(IPC_KEY, 4096, IPC_CREAT | 0664);
	if (shmid<0){
		perror("shmget error");
		return -1;
	}

	void *shm_start = shmat(shmid, NULL, 0);
	if (shm_start == (void*)-1){
		perror("shmat error");
		return -1;
	}
	int i = 0;
	while (1){

		sprintf(shm_start, "i am process A", i++);
		sleep(1);
	}
	shmdt(shm_start);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
//==============================================

#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>

#define IPC_KEY 0x12345678
#define PROJ_ID 0x11111111

int main(int argc, char *argv[]){

	int shmid = shmget(IPC_KEY, 4096, IPC_CREAT | 0664);
	if (shmid<0){
		perror("shmget error");
		return -1;
	}

	void *shm_start = shmat(shmid, NULL, 0);
	if (shm_start == (void*)-1){
		perror("shmat error");
		return -1;
	}

	while (1){

		printf("%s\n", (char*)shm_start);
		sleep(1);
	}
	shmdt(shm_start);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}