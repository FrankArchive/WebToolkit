#include"SocketWrapper.h"

bool Socket::initialize() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)return SocketStatusCode::init_failed;
	return SocketStatusCode::initialized;
}

int Socket::perform_listen(int max_connection) {
	int error_flag = 0, conn_handler;
	try_to_do((error_flag = listen(sock, max_connection)) == SOCKET_ERROR);
	if (error_flag == SOCKET_ERROR)return status = SocketStatusCode::runtime_error;
	while (1) {
		try_to_do((error_flag = conn_handler = accept(sock, (sockaddr*)NULL, NULL)) == SOCKET_ERROR);
		if (error_flag == SOCKET_ERROR)return status = SocketStatusCode::runtime_error;
	}
}

int Socket::perform_connect(int port) {
	int error_flag = SOCKET_ERROR;
	sockaddr_in address = { AF_INET };

	hostent *HostInfo = 0;
	try_to_do((HostInfo = gethostbyname(host.c_str())) == 0);
	if (HostInfo == 0)return status = SocketStatusCode::connect_failed;

	address.sin_port = htons(port);
	memcpy(&address.sin_addr, HostInfo->h_addr, 4);

	try_to_do((error_flag = connect(sock, (sockaddr*)&address, sizeof(address))) == SOCKET_ERROR);
	if (error_flag == SOCKET_ERROR)return status = SocketStatusCode::connect_failed;

	return status = SocketStatusCode::connected;
}

int Socket::perform_send(string request) {
	memset(buffer, 0, sizeof(buffer));
	int fflag = 0;
	try_to_do((fflag = send(sock, request.c_str(), request.size(), 0)) == SOCKET_ERROR);

	if (fflag == SOCKET_ERROR)return status = SocketStatusCode::send_failed;
	return status = SocketStatusCode::msg_sent;
}

int Socket::perform_recieve() {
	result = "";
	if (status != SocketStatusCode::msg_sent)
		return SocketStatusCode::request_error;
	int recieved_bytes;
	Sleep(500);
	while (recieved_bytes = recv(sock, buffer, sizeof(buffer) - 1, 0))
		result += buffer;
	return status = SocketStatusCode::connected;
}

int SocketPool::add_client(string host, int port) {
	Socket * targ = pool[host] = new Socket;
	if (targ->status == SocketStatusCode::init_failed)
		return targ->status;
	targ->host = host;

	targ->status = pool[host]->perform_connect(port);
	if (targ->status == SocketStatusCode::connect_failed)
		return targ->status;

	return targ->status;
}

int SocketPool::destroy(string host) {
	delete pool[host];
	pool.erase(host);
	return 0;
}

Socket * SocketPool::operator[](string host) {
	return pool[host];
}
