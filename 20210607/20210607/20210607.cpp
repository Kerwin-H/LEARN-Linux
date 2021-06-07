#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define CHECK_RET(q) if((q)==false){return -1;}
#define LISTEN_BACKLOG 5

class TcpSocket{
private:
	int _sockfd;    
public:

	TcpSocket() :_sockfd(-1){}   
	
	bool Socket() {
		_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_sockfd < 0) {  
			perror("socket error");
			return false;
		}
		return true;
	}
	
	bool Bind(const std::string &ip, const uint16_t port){
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);    
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);    
		int ret = bind(_sockfd, (sockaddr*)&addr, len); 
		if (ret < 0) {     
			perror("bind error");
			return false;
		}
		return true;
	}
	
	bool Listen(int backlog = LISTEN_BACKLOG) {
		
		int ret = listen(_sockfd, backlog);
		if (ret < 0) {     
			perror("listen error");
			return false;
		}
		return true;
	}
	
	bool Connect(const std::string &ip, const int port) {
		sockaddr_in addr;       
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);
		
		int ret = connect(_sockfd, (sockaddr*)&addr, len);
		if (ret < 0) { 
			perror("connect error");
			return false;
		}
		return true;
	}
	
	bool Accept(TcpSocket *sock, std::string *ip = NULL,
		uint16_t *port = NULL) {
		
		sockaddr_in addr;
		socklen_t len = sizeof(sockaddr_in);
		int newfd = accept(_sockfd, (sockaddr*)&addr, &len);
		if (newfd < 0) {      
			perror("accept error");
			return false;
		}
		
		sock->_sockfd = newfd;

		if (ip != NULL) {
			*ip = inet_ntoa(addr.sin_addr);     
		}
		if (port != NULL) {
			*port = ntohs(addr.sin_port);     
		}
		return true;
	}
	
	bool Recv(std::string *buf) {
	
		char tmp[4096] = { 0 };
		int ret = recv(_sockfd, tmp, 4096, 0);   
		if (ret < 0) {   
			perror("recv error");
			return false;
		}
		else if (ret == 0) {
			printf("peer shutdown");
			return false;
		}
		buf->assign(tmp, ret); 
		return true;
	}
	
	bool Send(const std::string &data) {
		
		int total = 0;  
		while (total < data.size()) {
			int ret = send(_sockfd, &data[0] + total,
				data.size() - total, 0);
			if (ret < 0) {  
				perror("send error");
				return false;
			}
			total += ret; 
		}
		return true;
	}

	bool Close() {
		if (_sockfd != -1) {    
			close(_sockfd);
		}
		return true;
	}
};
