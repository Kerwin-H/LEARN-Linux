#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond_customer;
pthread_cond_t cond_cooker;
int bowl = 1;//1表示杯中有水
void *cooker(void *arg)
{
	while (1) {
		//加锁
		pthread_mutex_lock(&mutex);
		while (bowl == 1) {
			//等待
			pthread_cond_wait(&cond_cooker, &mutex);
		}
		//倒水
		printf("倒好了水~\n");
		bowl++;
		//唤醒顾客
		pthread_cond_signal(&cond_customer);
		//解锁
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void *customer(void *arg)
{
	while (1) {
		//加锁
		pthread_mutex_lock(&mutex);
		while (bowl == 0) {
			//等待
			pthread_cond_wait(&cond_customer, &mutex);
		}
		//喝水
		printf("真香~\n");
		bowl--;
		//唤醒厨师
		pthread_cond_signal(&cond_cooker);
		//解锁
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
	int main(int argc, int argv[]){
		pthread_t ctid, dtid;
		int ret;

		pthread_mutex_init(&mutex, NULL);
		pthread_cond_init(&cond_cooker, NULL);
		pthread_cond_init(&cond_customer, NULL);
		int i = 0;
		for (i; i < 4; i++) {
			ret = pthread_create(&ctid, NULL, cooker, NULL);
			if (ret != 0) {
				printf("thread create error\n");
				return -1;
			}
		}
		int j = 0;
		for (j; j < 4; j++) {
			ret = pthread_create(&dtid, NULL, customer, NULL);
			if (ret != 0) {
				printf("thread create error\n");
				return -1;
			}
		}
		pthread_join(ctid, NULL);
		pthread_join(dtid, NULL);
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond_cooker);
		pthread_cond_destroy(&cond_customer);
		return 0;
	}