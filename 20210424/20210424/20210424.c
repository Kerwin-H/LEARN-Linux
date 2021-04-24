#include <iostream>
#include <queue>
#include <pthread.h>

#define MAX_QUEUE   10
#define MAX_THREAD  5

typedef void(*handler_t)(int data);

class ThreadTask{
private:
	int _data;//要处理的数据
	handler_t _handler;
public:
	ThreadTask() {}
	ThreadTask(int data, handler_t handler) :
		_data(data), _handler(handler){}
	void SetTask(int data, handler_t handler) {
		_data = data;
		_handler = handler;
	}
	void Run() {
		return _handler(_data);
	}
};

class BlockQueue{
private:
	int _capacity;//容量
	std::queue<ThreadTask> _queue;
	pthread_mutex_t _mutex;
	pthread_cond_t _cond_pro;
	pthread_cond_t _cond_cus;
public:
	BlockQueue(int cap = MAX_QUEUE) :_capacity(cap) {
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
	ThreadPool(int tnum = MAX_THREAD,
		int qnum = MAX_QUEUE) :_thread_num(tnum),
		_queue(qnum){}
	bool Init(){
		int ret;
		pthread_t tid;
		for (int i = 0; i < _thread_num; i++) {
			ret = pthread_create(&tid, NULL,
				thr_entry, (void*)this);
			if (ret != 0) {
				std::cout << "thread create error\n";
				return false;
			}
			pthread_detach(tid);
		}
		return true;
	}
	bool Push(ThreadTask &task){
		_queue.Push(task);
		return true;
	}
private:
	static void *thr_entry(void *arg) {
		ThreadPool *p = (ThreadPool*)arg;
		while (1) {
			ThreadTask task;
			p->_queue.Pop(&task);
			task.Run();
		}
		return NULL;
	}
private:
	int _thread_num;
	BlockQueue _queue;
};

int main(int argc, char *argv[])
{
	return 0;
}
