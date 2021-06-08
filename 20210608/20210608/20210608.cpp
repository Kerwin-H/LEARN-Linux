#include "tcpsocket.hpp"
#include <sstream>

int main(int argc, char *argv[])
{

	if (argc != 3) {		//判断首行是有三串字符
		printf("usage: ./tcp_src 172.17.0.16 9000\n");	//这里是对应的公网地址,选择arg0
		return -1;
	}
	std::string srvip = argv[1];	//取出对应的请求方法
	uint16_t srvport = std::stoi(argv[2]);		//对对应的URI进行转换
	TcpSocket lst_sock;	//定义对应的socket结构体

	CHECK_RET(lst_sock.Socket());	

	CHECK_RET(lst_sock.Bind(srvip, srvport));	//绑定

	CHECK_RET(lst_sock.Listen());	//监听
	while (1) {		//循环内部开始通信

		TcpSocket clisock;		//取出对应的相关信息
		std::string cliip;
		uint16_t cliport;
		bool ret = lst_sock.Accept(&clisock, &cliip, &cliport);		//接受数据
		if (ret == false) {
			continue;
		}
		std::string buf;
		clisock.Recv(&buf);		//接受
		std::cout << "request:[" << buf << "]\n";

		std::string body;		//下面是正文对对应的数据在网页上表达
		body = "<html><body><h1>Hello Bit</h1></body></html>";
		std::stringstream ss;
		ss << "HTTP/1.1 500 OK\r\n";
		ss << "Connection: close\r\n";
		ss << "Content-Length: " << body.size() << "\r\n";
		ss << "Content-Type: text/html\r\n";
		ss << "Location: http://www.baidu.com\r\n";
		ss << "\r\n";
		ss << body;
		clisock.Send(ss.str());		//发送
		clisock.Close();	//短连接则关闭
	}

	lst_sock.Close();	//关闭对应的socket
}