#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
	//通过参数传入要连接的服务端的地址信息
	if (argc != 3) {
		printf("usage: ./tcp_cli srvip srvport\n");
		return -1;
	}
	std::string srvip = argv[1];
	uint16_t srvport = std::stoi(argv[2]);

	TcpSocket cli_sock;
	//1. 创建套接字
	CHECK_RET(cli_sock.Socket());
	//2. 绑定地址信息（不推荐）
	//3. 向服务端发起连接
	CHECK_RET(cli_sock.Connect(srvip, srvport));
	while (1) {
		//4. 收发数据
		std::string buf;
		std::cout << "client say: ";
		std::cin >> buf;
		CHECK_RET(cli_sock.Send(buf));

		buf.clear();
		CHECK_RET(cli_sock.Recv(&buf));
		std::cout << "server say: " << buf << std::endl;
	}
	//5. 关闭套接字
	CHECK_RET(cli_sock.Close());
	return 0;
}

#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
	//通过程序运行参数指定服务端要绑定的地址
	// ./tcp_srv 192.168.2.2 9000
	if (argc != 3) {
		printf("usage: ./tcp_src 192.168.2.2 9000\n");
		return -1;
	}
	std::string srvip = argv[1];
	uint16_t srvport = std::stoi(argv[2]);
	TcpSocket lst_sock;//监听套接字
	//1. 创建套接字
	CHECK_RET(lst_sock.Socket());
	//2. 绑定地址信息
	CHECK_RET(lst_sock.Bind(srvip, srvport));
	//3. 开始监听
	CHECK_RET(lst_sock.Listen());
	while (1) {
		//4. 获取新建连接
		TcpSocket clisock;
		std::string cliip;
		uint16_t cliport;
		bool ret = lst_sock.Accept(&clisock, &cliip, &cliport);
		if (ret == false) {
			continue;
		}
		std::cout << "get newconn:" << cliip << "-" << cliport << "\n";
		//5. 收发数据--使用获取的新建套接字进行通信
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
	//6. 关闭套接字
	lst_sock.Close();
}
