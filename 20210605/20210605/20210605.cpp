#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
	//ͨ����������Ҫ���ӵķ���˵ĵ�ַ��Ϣ
	if (argc != 3) {
		printf("usage: ./tcp_cli srvip srvport\n");
		return -1;
	}
	std::string srvip = argv[1];
	uint16_t srvport = std::stoi(argv[2]);

	TcpSocket cli_sock;
	//1. �����׽���
	CHECK_RET(cli_sock.Socket());
	//2. �󶨵�ַ��Ϣ�����Ƽ���
	//3. �����˷�������
	CHECK_RET(cli_sock.Connect(srvip, srvport));
	while (1) {
		//4. �շ�����
		std::string buf;
		std::cout << "client say: ";
		std::cin >> buf;
		CHECK_RET(cli_sock.Send(buf));

		buf.clear();
		CHECK_RET(cli_sock.Recv(&buf));
		std::cout << "server say: " << buf << std::endl;
	}
	//5. �ر��׽���
	CHECK_RET(cli_sock.Close());
	return 0;
}

#include "tcpsocket.hpp"

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
		std::cout << "get newconn:" << cliip << "-" << cliport << "\n";
		//5. �շ�����--ʹ�û�ȡ���½��׽��ֽ���ͨ��
		std::string buf;
		ret = clisock.Recv(&buf);
		if (ret == false) {
			clisock.Close();
			continue;
		}
		std::cout << "client say: " << buf << std::endl;

		buf.clear();
		std::cout << "server say: ";
		std::cin >> buf;
		ret = clisock.Send(buf);
		if (ret == false) {
			clisock.Close();
		}
	}
	//6. �ر��׽���
	lst_sock.Close();
}
