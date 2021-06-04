/*
TCP���ܷ�װ
���书�ܷ�װʵ�ֺ���ļ򵥵���
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
//��װTCPЭ������Ҫ�ĺ���
class TcpSocket{
private:
	int _sockfd;    //˽���Ƕ�Ӧ��������
public:

	TcpSocket() :_sockfd(-1){}   //���캯������������ʼ��Ϊ-1
	//1.====�����׽���
	bool Socket() {
		_sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_sockfd < 0) {  //�ж��Ƿ����
			perror("socket error");
			return false;
		}
		return true;
	}
	//2.====�󶨵�ַ��Ϣ
	bool Bind(const std::string &ip, const uint16_t port){
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);    //ת�ɶ�Ӧ�������ֽ���
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);    //�ֽڴ�С
		int ret = bind(_sockfd, (sockaddr*)&addr, len); //���ýӿ�ʵ�����ݵİ�
		if (ret < 0) {      //�ж��Ƿ����
			perror("bind error");
			return false;
		}
		return true;
	}
	//3.====��ʼ����
	bool Listen(int backlog = LISTEN_BACKLOG) {
		//listen(��������ͬһʱ��������)
		int ret = listen(_sockfd, backlog);
		if (ret < 0) {      //�ж��Ƿ����
			perror("listen error");
			return false;
		}
		return true;
	}
	//4.====�ͻ��˷�����������
	bool Connect(const std::string &ip, const int port) {
		sockaddr_in addr;       //�����Ӧ��Ҫ�õ��Ĳ���
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = inet_addr(&ip[0]);
		socklen_t len = sizeof(sockaddr_in);
		//connect(������������˵�ַ�� ��ַ����)
		int ret = connect(_sockfd, (sockaddr*)&addr, len);
		if (ret < 0) {  //�ж��Ƿ����
			perror("connect error");
			return false;
		}
		return true;
	}
	//5.====����˻�ȡ�µ�����
	bool Accept(TcpSocket *sock, std::string *ip = NULL,
		uint16_t *port = NULL) {
		//int accept(�����׽��֣� ��ȥ�ͻ��˵�ַ�� ����)
		sockaddr_in addr;
		socklen_t len = sizeof(sockaddr_in);
		int newfd = accept(_sockfd, (sockaddr*)&addr, &len);
		if (newfd < 0) {        //���Ӻ��д�
			perror("accept error");
			return false;
		}
		//��Ϊ�����ｫ�ͻ��˺͸��ƺ��socket����������,
		//�����Ӧ�ý���Ӧ��������ָ����ͻ������ӵ�socket
		sock->_sockfd = newfd;

		if (ip != NULL) {
			*ip = inet_ntoa(addr.sin_addr);     //����Ӧ�������ֽ����IP��ַת���ַ������ʮ���Ƶ�IP��ַ
		}
		if (port != NULL) {
			*port = ntohs(addr.sin_port);       //��Ӧ��portΪ��,����Ӧ����������ת���ɶ�Ӧ�������ֽ���
		}
		return true;
	}
	//6.====��������
	bool Recv(std::string *buf) {
		//int recv(���������ռ䣬���ݳ��ȣ���־λ)
		//����ֵ��ʵ�ʻ�ȡ��С�� 0-���ӶϿ��� -1-������
		char tmp[4096] = { 0 };   //������Ӧ�Ĵ洢�ڴ�
		int ret = recv(_sockfd, tmp, 4096, 0);      //����Ӧ�����ݽ��н���
		if (ret < 0) {      //�д�
			perror("recv error");
			return false;
		}
		else if (ret == 0) {
			printf("peer shutdown");
			return false;
		}
		buf->assign(tmp, ret);  //�Դ�����ռ俽������
		return true;
	}
	//7.====��������
	bool Send(const std::string &data) {
		//int send(�����������ݣ����ȣ���־λ)
		int total = 0;  //��ʼ����������
		while (total < data.size()) {
			int ret = send(_sockfd, &data[0] + total,
				data.size() - total, 0);
			if (ret < 0) {  //�д�
				perror("send error");
				return false;
			}
			total += ret;   //���ڲ����������ݺ�����ݽ��м���
		}
		return true;
	}
	//8.====�ر��׽���
	bool Close() {
		if (_sockfd != -1) {        //������ر�
			close(_sockfd);
		}
		return true;
	}
};
