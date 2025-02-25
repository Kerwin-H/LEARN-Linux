/*
TCP功能封装
将其功能封装实现后面的简单调用
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define CHECK_RET(q) if((q)==false){return -1;}
#define LISTEN_BACKLOG 5
//封装TCP协议所需要的函数
class TcpSocket{
private:
	int _sockfd;    //私有是对应的描述符
public:

	TcpSocket() :_sockfd(-1){}   //构造函数将描述符初始化为-1
	//1.====创建套接字
	bool Socket() {
		_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_sockfd < 0) {  //判断是否出错
			perror("socket error");
			return false;
		}
		return true;
	}
	//2.====绑定地址信息
	bool Bind(const std::string &ip, const uint16_t port){
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);    //转成对应的网络字节序
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);    //字节大小
		int ret = bind(_sockfd, (sockaddr*)&addr, len); //调用接口实现数据的绑定
		if (ret < 0) {      //判断是否出错
			perror("bind error");
			return false;
		}
		return true;
	}
	//3.====开始监听
	bool Listen(int backlog = LISTEN_BACKLOG) {
		//listen(描述符，同一时间连接数)
		int ret = listen(_sockfd, backlog);
		if (ret < 0) {      //判断是否出错
			perror("listen error");
			return false;
		}
		return true;
	}
	//4.====客户端发送连接请求
	bool Connect(const std::string &ip, const int port) {
		sockaddr_in addr;       //引入对应需要用到的参数
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);
		//connect(描述符，服务端地址， 地址长度)
		int ret = connect(_sockfd, (sockaddr*)&addr, len);
		if (ret < 0) {  //判断是否出错
			perror("connect error");
			return false;
		}
		return true;
	}
	//5.====服务端获取新的连接
	bool Accept(TcpSocket *sock, std::string *ip = NULL,
		uint16_t *port = NULL) {
		//int accept(监听套接字， 回去客户端地址， 长度)
		sockaddr_in addr;
		socklen_t len = sizeof(sockaddr_in);
		int newfd = accept(_sockfd, (sockaddr*)&addr, &len);
		if (newfd < 0) {        //连接后判错
			perror("accept error");
			return false;
		}
		//因为在这里将客户端和复制后的socket发生了连接,
		//这里就应该将对应的描述符指向与客户端连接的socket
		sock->_sockfd = newfd;

		if (ip != NULL) {
			*ip = inet_ntoa(addr.sin_addr);     //将对应的网络字节序的IP地址转成字符串点分十进制的IP地址
		}
		if (port != NULL) {
			*port = ntohs(addr.sin_port);       //对应的port为空,将对应的网络数据转换成对应的主机字节序
		}
		return true;
	}
	//6.====接受数据
	bool Recv(std::string *buf) {
		//int recv(描述符，空间，数据长度，标志位)
		//返回值：实际获取大小， 0-连接断开； -1-出错了
		char tmp[4096] = { 0 };   //创建对应的存储内存
		int ret = recv(_sockfd, tmp, 4096, 0);      //将对应的数据进行接受
		if (ret < 0) {      //判错
			perror("recv error");
			return false;
		}
		else if (ret == 0) {
			printf("peer shutdown");
			return false;
		}
		buf->assign(tmp, ret);  //自带申请空间拷贝数据
		return true;
	}
	//7.====发送数据
	bool Send(const std::string &data) {
		//int send(描述符，数据，长度，标志位)
		int total = 0;  //初始化整型数据
		while (total < data.size()) {
			int ret = send(_sockfd, &data[0] + total,
				data.size() - total, 0);
			if (ret < 0) {  //判错
				perror("send error");
				return false;
			}
			total += ret;   //在内部发送完数据后对数据进行计数
		}
		return true;
	}
	//8.====关闭套接字
	bool Close() {
		if (_sockfd != -1) {        //存在则关闭
			close(_sockfd);
		}
		return true;
	}
};
