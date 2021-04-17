#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int tickets = 100;

void *scalpers(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t*)arg;
	while (1) {
		pthread_mutex_lock(mutex);
		if (tickets > 0) {
			usleep(1);
			printf("I got a ticket£º%d\n", tickets);
			tickets--;
		}
		else {
			pthread_mutex_unlock(mutex);
			pthread_exit(NULL);
		}
		pthread_mutex_unlock(mutex);
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	pthread_mutex_t mutex;
	pthread_t tid[4];
	int ret;
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < 4; i++) {
		ret = pthread_create(&tid[i], NULL, scalpers, NULL);
		if (ret != 0) {
			printf("thread create error\n");
			return -1;
		}
	}
}
for (int i = 0; i < 4; i++) {
	pthread_join(tid[i], NULL);
}
pthread_mutex_destroy(&mutex);
return 0;
}
