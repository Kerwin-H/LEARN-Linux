#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_entry(void *arg)
{
	pthread_detach(pthread_self());
	char *ptr = "hello \n";
	//char ptr[] = "hello bit\n";
	sleep(3);
	return (void*)ptr;
}
int main(int argc, char *argv[])
{
	pthread_t tid;
	int ret = pthread_create(&tid, NULL, thr_entry, NULL);
	if (ret != 0) {
		printf("thread create error\n");
		return -1;
	}
	//pthread_detach(tid);
	//pthread_join(线程tid， 获取返回值)
	//void *retval = NULL;
	//pthread_join(tid, &retval);
	//printf("retval:%s\n", retval);
	while (1) {
		printf("i am main thread\n");
		sleep(1);
	}
	return 0;
}
