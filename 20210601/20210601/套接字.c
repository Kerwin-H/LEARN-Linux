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
		printf("client say: %s\n", buf);
		//4. �ظ�����
		char *data = "�¿���~~";
		ret = sendto(sockfd, data, strlen(data), 0,
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
