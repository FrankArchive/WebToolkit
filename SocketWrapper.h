#ifndef SocketWrapper_h
#define SocketWrapper_h


#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#include<string>
using namespace std;
#define retry_time 5
//#define failed 1
//#define success 0

enum SocketErrorCode {
	success,
	initialization_failed,//please check your internet settings
	connection_failed//please check your internet connection
};

class SocketWrapper {
	WSAData word;
	char buffer[1024];
	SOCKET sock;
	int status;//current object status (e.g: normal / not initialized etc.)
	string host;

	bool initialize() {
		WSAStartup(MAKEWORD(2, 2), &word);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock == INVALID_SOCKET)return 1;
		return 0;
	}
public:
	SocketWrapper() { 
		for (int i = 0; i < retry_time && (status = initialize())/*==failed*/; i++);
		if (status/*==failed*/)
			status = SocketErrorCode::initialization_failed;
	}
	~SocketWrapper() { WSACleanup(); closesocket(sock); }
	int Send(string request, string host) {
		
	}
};

#endif