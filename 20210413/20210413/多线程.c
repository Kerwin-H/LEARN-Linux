#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_entry(void *arg)
{
	printf("%s\n", (char*)arg);
	while (1) {
		printf(" i am normal thread-%p-%d\n", pthread_self(), getpid());
		sleep(1);
		//pthread_exit(NULL);
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	pthread_t tid;
	int ret;
	char *ptr = "���������������\n";
	//pthread_create(��ȡID, ���ԣ� ��ں����� �������)
	ret = pthread_create(&tid, NULL, thr_entry, (void*)ptr);
	if (ret != 0) {
		printf("pthread_create failed!\n");
		return -1;
	}
	sleep(3);
	pthread_cancel(tid);
	while (1) {
		printf("i am main thread--%p-%d\n", pthread_self(), getpid());
		sleep(1);
	}
	return 0;
}
