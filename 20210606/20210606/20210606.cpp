#include "tcpsocket.hpp"
#include <sstream>

int main(int argc, char *argv[])
{
	//ͨ���������в���ָ�������Ҫ�󶨵ĵ�ַ
	// ./tcp_srv 192.168.2.2 9000
	if (argc != 3) {
		printf("usage: ./tcp_src 192.168.2.2 9000\n");
		return -1;
	}
	std::string srvip = argv[1];
	uint16_t srvport = std::stoi(argv[2]);
	TcpSocket lst_sock;//�����׽���
	//1. �����׽���
	CHECK_RET(lst_sock.Socket());
	//2. �󶨵�ַ��Ϣ
	CHECK_RET(lst_sock.Bind(srvip, srvport));
	//3. ��ʼ����
	CHECK_RET(lst_sock.Listen());
	while (1) {
		//4. ��ȡ�½�����
		TcpSocket clisock;
		std::string cliip;
		uint16_t cliport;
		bool ret = lst_sock.Accept(&clisock, &cliip, &cliport);
		if (ret == false) {
			continue;
		}
		std::string buf;
		clisock.Recv(&buf);
		std::cout << "request:[" << buf << "]\n";

		std::string body;
		body = "<html><body><h1>Hello Bit</h1></body></html>";
		std::stringstream ss;
		ss << "HTTP/1.1 500 OK\r\n";
		ss << "Connection: close\r\n";
		ss << "Content-Length: " << body.size() << "\r\n";
		ss << "Content-Type: text/html\r\n";
		ss << "Location: http://www.baidu.com\r\n";
		ss << "\r\n";
		ss << body;
		clisock.Send(ss.str());
		clisock.Close();
	}
	//6. �ر��׽���
	lst_sock.Close();
}
