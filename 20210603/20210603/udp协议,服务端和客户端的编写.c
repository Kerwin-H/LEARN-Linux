
#include "udpsocket.hpp"

#define CHECK_RET(q) if((q)==false){return -1;}
int main()
{
	UdpSocket sock;
	//1. �����׽���
	CHECK_RET(sock.Socket());
	//2. �󶨵�ַ��Ϣ�����Ƽ���
	while (1) {
		//3. ��������
		std::cout << "client say: ";
		std::string buf;
		std::cin >> buf;
		CHECK_RET(sock.Send(buf, "172.17.0.3", 9000));
		//4. ��������
		buf.clear();
		CHECK_RET(sock.Recv(&buf));
		std::cout << "server say: " << buf << "\n";
	}
	//5. �ر��׽���
	sock.Close();
	return 0;
}



#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>//�ֽ���ת���ӿ�ͷ�ļ�
#include <netinet/in.h>//��ַ�ṹͷ��Э�������ļ�
#include <sys/socket.h>//�׽��ֽӿ�ͷ�ļ�

int main()
{
	//1. �����׽���
	// int socket(��ַ�����ͣ� �׽������ͣ� Э������)
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) {
		perror("socket error");
		return -1;
	}
	//2. Ϊ�׽��ְ󶨵�ַ��Ϣ
	// int bind(�׽����������� ��ַ��Ϣ��  ��ַ����)
	struct sockaddr_in addr;//����IPv4��ַ�ṹ
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000); //���õ�ַ�˿�
	addr.sin_addr.s_addr = inet_addr("172.17.0.3");
	int len = sizeof(addr);
	int ret = bind(sockfd, (struct sockaddr*)&addr, len);
	if (ret < 0) {
		perror("bind error");
		return -1;
	}
	while (1){
		//3. ��������
		// recvfrom(���, �ռ�,���ȣ���־���Զ˵�ַ����ַ����)
		char buf[1024] = { 0 };
		struct sockaddr_in paddr;
		int len = sizeof(struct sockaddr_in);
		ret = recvfrom(sockfd, buf, 1023, 0,
			(struct sockaddr*)&paddr, &len);
		if (ret < 0) {
			perror("recvfrom error");	
			return -1;
		}
		uint16_t cport = ntohs(paddr.sin_port);
		char *cip = inet_ntoa(paddr.sin_addr);
		printf("client-[%s:%d] say: %s\n", cip, cport, buf);
		//4. �ظ�����
		memset(buf, 0x00, 1024);
		printf("server say: ");
		fflush(stdout);
		fgets(buf, 1023, stdin);
		ret = sendto(sockfd, buf, strlen(buf), 0,
			(struct sockaddr*)&paddr, len);
		if (ret < 0) {
			perror("sendto error");
			return -1;
		}
	}
	//5. �ر��׽���
	close(sockfd);
	return 0;
}
