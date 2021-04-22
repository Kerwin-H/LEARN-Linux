#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdio.h>

#define MAX_QUEUE 5

class BlockQueue{

private:
	int _capacity;
	std::queue<int> _queue;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond_pro;
	pthread_cond_t _cond_cus;

public:

	BlockQueue(int cap = MAX_QUEUE)
		:_capacity(cap)
	{
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond_pro, NULL);
		pthread_cond_init(&_cond_cus, NULL);
	}

	~BlockQueue(){

		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond_pro);
		pthread_cond_destroy(&_cond_cus);
	}
	bool Push(int data){

		pthread_mutex_lock(&_mutex);
		while (_queue.size() == _capacity){
			pthread_cond_wait(&_cond_pro, &_mutex);
		}
		_queue.push(data);
		pthread_cond_signal(&_cond_cus);
		pthread_mutex_unlock(&_mutex);
		return true;
	}
	bool Pop(int *data){

		pthread_mutex_lock(&_mutex);
		while (_queue.empty()){

			pthread_cond_wait(&_cond_cus, &_mutex);
		}
		*data = _queue.front();
		_queue.pop();
		pthread_cond_signal(&_cond_pro);
		pthread_mutex_unlock(&_mutex);
		return true;
	}
};

void *productor(void *arg){

	BlockQueue *q = (BlockQueue*)arg;
	int i = 0;
	while (1){
		q->Push(i);
		printf("%p--push  data:%d\n", pthread_self(), i++);
	}
	return NULL;
}

void *customer(void *arg){

	BlockQueue *q = (BlockQueue*)arg;
	while (1){
		int data;
		q->Pop(&data);
		printf("%p-get data: %d\n", pthread_self(), data);
	}
	return NULL;
}


int main(int argc, char *argv[]){

	BlockQueue q;
	int count = 4, ret;

	pthread_t ptid[4], ctid[4];
	//注意这里的i值对于两个线程是一致的,不要随便改变
	//否则会发现只能push出来而不能get到    
	for (int i = 0; i<count; i++){
		ret = pthread_create(&ptid[i], NULL, productor, &q);
		if (ret != 0){
			printf("thread create error\n");
			return -1;
		}
	}
	for (int i = 0; i<count; i++){
		ret = pthread_create(&ctid[i], NULL, customer, &q);
		if (ret != 0){
			printf("thread create error\n");
			return -1;
		}
	}
	for (int i = 0; i<count; i++){
		pthread_join(ptid[i], NULL);
		pthread_join(ctid[i], NULL);
	}
	return 0;
}
