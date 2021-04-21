#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond_customer;
pthread_cond_t cond_cooker;
int bowl = 1;//1��ʾ������ˮ
void *cooker(void *arg)
{
	while (1) {
		//����
		pthread_mutex_lock(&mutex);
		while (bowl == 1) {
			//�ȴ�
			pthread_cond_wait(&cond_cooker, &mutex);
		}
		//��ˮ
		printf("������ˮ~\n");
		bowl++;
		//���ѹ˿�
		pthread_cond_signal(&cond_customer);
		//����
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}
void *customer(void *arg)
{
	while (1) {
		//����
		pthread_mutex_lock(&mutex);
		while (bowl == 0) {
			//�ȴ�
			pthread_cond_wait(&cond_customer, &mutex);
		}
		//��ˮ
		printf("����~\n");
		bowl--;
		//���ѳ�ʦ
		pthread_cond_signal(&cond_cooker);
		//����
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