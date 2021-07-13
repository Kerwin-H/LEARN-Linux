#include<iostream>
#include<vector>
#include<time.h>
#include<sys/select.h>
#include"tcpsocket.hpp"

class Select{

public:
	Select() :_max_fd(-1){   //初始化
		FD_ZERO(&_rfds);    //归0
	}
	bool Add(const TcpSocket &sock){ //添加监控

		int fd = sock.GetFd();
		FD_SET(fd, &_rfds);
		_max_fd = _max_fd > fd ? _max_fd : fd;
		return true;
	}
	bool Del(const TcpSocket &sock){ //移除监控

		int fd = sock.GetFd();
		FD_CLR(fd, &_rfds);
		for (int i = _max_fd; i >= 0; i--){
			if (FD_IDDET(i, &_rfds)){
				_max_fd = i;
				break;
			}
			return true;
		}

	}
	//通过参数返回就绪的套接字数组
	bool Wait(std::vector<TcpSocket> *arry){
		struct timeval tv;
		tv.tv_sec = 3;
		tv.tv_usec = 0;
		fd_set tmp = _rfds;
		//select(max+1,读,写,异常,超时)
		int ret = select(_max_fd + 1, &tmp, NULL, NULL, &tv);
		if (ret<0){
			perror("select error");
			return false;
		}
		else if (ret == 0){
			arry->clear();
			return true;
		}
		for (int i = 0; i <= _max_fd; i++){
			if (FD_ISSET(i, &tmp)){
				TcpSocket sock;
				sock.SetFd(i);
				arry->pushback(sock);
			}
		}
		return true;
	}
private:
	fd_set _rfd; //需要监控的描述符集合
	int _max_fd; //保存当前集合中最大的描述符
};
