#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

#define MAX_QUEUE 5
class RingQueue
{
private:
	int _capacity;
	int _step_read;
	int _step_write;
	std::vector<int> _arry;
	sem_t _sem_lock;
	sem_t _sem_idle;
	sem_t _sem_data;
public:
	RingQueue(int cap = MAX_QUEUE) :_capacity(cap),
		_step_read(0), _step_write(0), _arry(cap){
		//sem_init(信号量，共享标志， 初值)
		sem_init(&_sem_lock, 0, 1);
		sem_init(&_sem_idle, 0, cap);
		sem_init(&_sem_data, 0, 0);
	}
	~RingQueue(){
		sem_destroy(&_sem_lock);
		sem_destroy(&_sem_idle);
		sem_destroy(&_sem_data);
	}
	bool Push(int data) {
		sem_wait(&_sem_idle);//空闲空间数量-1；<0阻塞
		sem_wait(&_sem_lock);//加锁
		_arry[_step_write] = data;
		_step_write = (_step_write + 1) % _capacity;
		sem_post(&_sem_lock);//解锁
		sem_post(&_sem_data);//数据空间数量+1;唤醒消费
		return true;
	}
	bool Pop(int *data) {
		sem_wait(&_sem_data);
		sem_wait(&_sem_lock);
		*data = _arry[_step_read];
		_step_read = (_step_read + 1) % _capacity;
		sem_post(&_sem_lock);
		sem_post(&_sem_idle);
		return true;
	}
};


void *productor(void *arg)
{
	RingQueue *q = (RingQueue*)arg;
	int i = 0;
	while (1) {
		q->Push(i);
		printf("%p-push data:%d\n", pthread_self(), i++);
	}
	return NULL;
}
void *customer(void *arg)
{
	RingQueue *q = (RingQueue*)arg;
	while (1) {
		int data;
		q->Pop(&data);
		printf("%p-get data:%d\n", pthread_self(), data);
	}
	return NULL;
}
int main(int argc, char *argv[])
{
	RingQueue q;
	int count = 4, ret;
	pthread_t ptid[4], ctid[4];
	for (int i = 0; i < count; i++) {
		ret = pthread_create(&ptid[i], NULL, productor, &q);
		if (ret != 0) {
			printf("thread create error\n");
			return -1;
		}
	}
	for (int i = 0; i < count; i++) {
		ret = pthread_create(&ctid[i], NULL, customer, &q);
		if (ret != 0) {
			printf("thread create error\n");
			return -1;
		}
	}
	for (int i = 0; i < count; i++) {
		pthread_join(ptid[i], NULL);
		pthread_join(ctid[i], NULL);
	}
	return 0;
}
