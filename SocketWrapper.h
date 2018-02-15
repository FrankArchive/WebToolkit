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
	runtime_error, request_error
};
class Socket {
	char buffer[1024];
	SOCKET sock;
	int status;//current object status (e.g: normal / not initialized etc.)
	string host;//服务端域名
	string result;//recv存储的信息

	friend class SocketPool;

	bool initialize();
public:
	Socket() { try_to_do((status = initialize()) == SocketStatusCode::init_failed); }
	~Socket() { closesocket(sock); }

	//server
	int perform_listen(int max_connection);

	//client
	int perform_connect(int port);
	int perform_send(string request);
	int perform_recieve();
	string get_result() { return result; }
};

class SocketPool {
	unordered_map<string, Socket*>pool;
	WSAData data;
public:
	SocketPool() { WSAStartup(MAKEWORD(2, 2), &data); }
	~SocketPool() { WSACleanup(); }

	int add_client(string host, int port = 80);
	int destroy(string host);
};

#endif