#include <cstdio>
#include <iostream>
#include <queue>
#include <unistd.h>
#include <pthread.h>

typedef void(*handler_t)(int);
class ThreadTask{
private:
	int _data;//任务处理的数据
	handler_t _handler;//数据的处理方法
public:
	ThreadTask(){}
	ThreadTask(int data, handler_t handler) :
		_data(data), _handler(handler){}
	void Run() {//线程池中的线程获取节点后只需要调用run
		_handler(_data);
	}
};
class BlockQueue{
private:
	int _capacity;
	std::queue<ThreadTask> _queue;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond_pro;
	pthread_cond_t _cond_cus;
public:
	BlockQueue(int cap = 5) :_capacity(cap){
		pthread_mutex_init(&_mutex, NULL);
		pthread_cond_init(&_cond_pro, NULL);
		pthread_cond_init(&_cond_cus, NULL);
	}
	~BlockQueue() {
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond_pro);
		pthread_cond_destroy(&_cond_cus);
	}
	bool Push(ThreadTask &data) {
		pthread_mutex_lock(&_mutex);
		while (_queue.size() == _capacity) {
			pthread_cond_wait(&_cond_pro, &_mutex);
		}
		_queue.push(data);
		pthread_cond_signal(&_cond_cus);
		pthread_mutex_unlock(&_mutex);
		return true;
	}
	bool Pop(ThreadTask *data) {
		pthread_mutex_lock(&_mutex);
		while (_queue.empty()) {
			pthread_cond_wait(&_cond_cus, &_mutex);
		}
		*data = _queue.front();
		_queue.pop();
		pthread_cond_signal(&_cond_pro);
		pthread_mutex_unlock(&_mutex);
		return true;
	}
};

class ThreadPool
{
public:
	ThreadPool(int thr = 5, int que = 10) :_max_thread(thr),
		_max_queue(que), _queue(que){
		int ret;
		pthread_t tid;
		for (int i = 0; i < thr; i++) {
			ret = pthread_create(&tid, NULL,
				entry, this);
			if (ret != 0) {
				printf("thread create failed!\n");
				exit(-1);
			}
			pthread_detach(tid);
		}
	}
	bool TaskPush(ThreadTask &task) {
		_queue.Push(task);
		return true;
	}
private:
	static void *entry(void *arg) {
		ThreadPool *pool = (ThreadPool*)arg;
		while (1) {
			ThreadTask task;
			pool->_queue.Pop(&task);
			task.Run();
		}
		return NULL;
	}
private:
	int _max_thread;
	int _max_queue;
	BlockQueue _queue;
};

void test(int data)
{
	printf("i am thr:%p-get data:%d, will sleep:%d s\n",
		pthread_self(), data, data % 5);
	sleep(data % 5);
}
int main()
{
	ThreadPool pool;

	for (int i = 0; i < 10; i++) {
		ThreadTask task(i, test);
		pool.TaskPush(task);
	}
	while (1) sleep(1);
	return 0;
}
