#ifndef SocketWrapper_h
#define SocketWrapper_h


#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<string>
#include<unordered_map>
#include<vector>
using namespace std;
#define retry_time 5
#define try_to_do(x) for (int i = 0; i < retry_time && (x); i++)

//#define failed 1
//#define success 0

enum SocketStatusCode {
	initialized, init_failed,
	connected, connect_failed,
	msg_sent, send_failed,
	runtime_error
};
class Socket {
	char buffer[1024];
	SOCKET sock;
	int status;//current object status (e.g: normal / not initialized etc.)
	string host;

	friend class SocketPool;

	bool initialize() {
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)return SocketStatusCode::init_failed;
		return SocketStatusCode::initialized;
	}
public:
	Socket() {
		try_to_do((status = initialize()) == SocketStatusCode::init_failed);
	}
	~Socket() { closesocket(sock); }


	//server
	int perform_listen(int max_connection) {
		int error_flag = 0, conn_handler;
		try_to_do((error_flag = listen(sock, max_connection)) == SOCKET_ERROR);
		if (error_flag == SOCKET_ERROR)return SocketStatusCode::runtime_error;
		while (1) {
			try_to_do((error_flag = conn_handler = accept(sock, (sockaddr*)NULL, NULL)) == SOCKET_ERROR);
			if (error_flag == SOCKET_ERROR)return SocketStatusCode::runtime_error;
		}
	}
	//client
	int perform_connect(int port) {
		int error_flag = SOCKET_ERROR;
		sockaddr_in address = { AF_INET };

		try_to_do((error_flag = bind(sock, (sockaddr*)&address, sizeof(address))) == SOCKET_ERROR);
		if (error_flag == SOCKET_ERROR)return SocketStatusCode::connect_failed;

		hostent *HostInfo = 0;
		try_to_do((HostInfo = gethostbyname(host.c_str())) == 0);
		if (HostInfo == 0)return SocketStatusCode::connect_failed;

		address.sin_port = htons(port);
		memcpy(&address.sin_addr, HostInfo->h_addr, 4);

		try_to_do((error_flag = connect(sock, (sockaddr*)&address, sizeof(address))) == SOCKET_ERROR);
		if (error_flag == SOCKET_ERROR)return SocketStatusCode::connect_failed;

		return SocketStatusCode::connected;
	}

	int perform_send(string request) {
		int fflag = 0;
		try_to_do((fflag = send(sock, request.c_str(), request.size(), 0)) == SOCKET_ERROR);

		if (fflag == SOCKET_ERROR)return SocketStatusCode::send_failed;
		return SocketStatusCode::msg_sent;
	}
};

class SocketPool {
	unordered_map<string, Socket*>pool;
	WSAData data;
public:
	SocketPool() { WSAStartup(MAKEWORD(2, 2), &data); }
	~SocketPool() { WSACleanup(); }

	int add_client(string host, int port = 80) {
		Socket * targ = pool[host] = new Socket;
		if (targ->status == SocketStatusCode::init_failed)
			return targ->status;

		targ->status = pool[host]->perform_connect(port);
		if (targ->status == SocketStatusCode::connect_failed)
			return targ->status;
	}

	int destroy(string host) {
		delete pool[host];
		pool.erase(host);
	}
};

#endif