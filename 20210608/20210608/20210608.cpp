#include "tcpsocket.hpp"
#include <sstream>

int main(int argc, char *argv[])
{

	if (argc != 3) {		//�ж��������������ַ�
		printf("usage: ./tcp_src 172.17.0.16 9000\n");	//�����Ƕ�Ӧ�Ĺ�����ַ,ѡ��arg0
		return -1;
	}
	std::string srvip = argv[1];	//ȡ����Ӧ�����󷽷�
	uint16_t srvport = std::stoi(argv[2]);		//�Զ�Ӧ��URI����ת��
	TcpSocket lst_sock;	//�����Ӧ��socket�ṹ��

	CHECK_RET(lst_sock.Socket());	

	CHECK_RET(lst_sock.Bind(srvip, srvport));	//��

	CHECK_RET(lst_sock.Listen());	//����
	while (1) {		//ѭ���ڲ���ʼͨ��

		TcpSocket clisock;		//ȡ����Ӧ�������Ϣ
		std::string cliip;
		uint16_t cliport;
		bool ret = lst_sock.Accept(&clisock, &cliip, &cliport);		//��������
		if (ret == false) {
			continue;
		}
		std::string buf;
		clisock.Recv(&buf);		//����
		std::cout << "request:[" << buf << "]\n";

		std::string body;		//���������ĶԶ�Ӧ����������ҳ�ϱ��
		body = "<html><body><h1>Hello Bit</h1></body></html>";
		std::stringstream ss;
		ss << "HTTP/1.1 500 OK\r\n";
		ss << "Connection: close\r\n";
		ss << "Content-Length: " << body.size() << "\r\n";
		ss << "Content-Type: text/html\r\n";
		ss << "Location: http://www.baidu.com\r\n";
		ss << "\r\n";
		ss << body;
		clisock.Send(ss.str());		//����
		clisock.Close();	//��������ر�
	}

	lst_sock.Close();	//�رն�Ӧ��socket
}