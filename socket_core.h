#pragma once
#pragma once
#include<WinSock2.h>
#include<iostream>
#include<Windows.h>
using namespace std;
SOCKET sock;
string resultPage;
string request;
char buffer[1024];
void Send(string &request, string &host) {
retry:;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		closesocket(sock);
		goto retry;
	}

	sockaddr_in address = { AF_INET };

	if (bind(sock, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}
	hostent *HostInfo = gethostbyname(host.c_str());
	if (HostInfo == 0) {
		closesocket(sock);
		goto retry;
	}

	address.sin_port = htons(80);
	memcpy(&address.sin_addr, HostInfo->h_addr, 4);

	if (connect(sock, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}

	if (send(sock, request.c_str(), request.size(), 0) == SOCKET_ERROR) {
		closesocket(sock);
		goto retry;
	}
}

void Recieve(string &result) {
	int recive;
	while (recive = recv(sock, buffer, sizeof(buffer) - 1, 0))
		result += buffer;
}


//universal getpage function
string *getPage(string host, string directory) {
	resultPage = "";
	request = "GET " + directory + " HTTP/1.1\r\nHost: " + host + "\r\nConnection:Close\r\n\r\n";

	Send(request, host);
	Sleep(1000);
	Recieve(resultPage);

	closesocket(sock);
	return &resultPage;
}

//string *getPageWithJSESSIONID(string &JsessionID, string &host, string &directory) {
//	resultPage = "";
//	request = "GET " + directory + " HTTP/1.1\r\n" +
//		"Host: " + host + "\r\n" +
//		"Connection:Close\r\n" +
//		"Cookie: JSESSIONID=" + JsessionID + "\r\n" +
//		"\r\n";
//
//	Send(request, host);
//	Sleep(1000);
//	Recieve(resultPage);
//
//	closesocket(sock);
//	return &resultPage;
//}
string Int2String(int);
//login to poj.org
void PostDataWithJSESSIONID(string &JsessionID, string &data, string &dir, string &host) {
	request = (string)"POST http://" + host + dir + " HTTP/1.1\r\n" +
		"Content-Type: application/x-www-form-urlencoded\r\n" +
		"Content-Length: " + Int2String(data.length()) + "\r\n" +
		"Host:" + host + "\r\n" +
		"Connection: Keep-Alive\r\n" +
		"Pragma: no-cache\r\n" +
		"Accept: text/html, application/xhtml+xml, image/jxr, */*\r\n" +
		"Cookie: JSESSIONID=" + JsessionID + "\r\n" +
		"\r\n" + data;


	Send(request, host);

	closesocket(sock);
	return;
}
//
//string *getJSESSIONID(string &host) {
//	getPage(host, (string)"/");
//
//	int cookiePos = match(resultPage, (string)"JSESSIONID=") + 11;
//	int scout = cookiePos;
//	while (resultPage[scout] != ';')scout++;
//	resultPage = resultPage.substr(cookiePos, scout - cookiePos);
//
//	return &resultPage;
//}

string *getCOOKIE(string &host) {
	getPage(host, (string)"/");

	int cookiePos = match(resultPage, (string)"JSESSIONID=") + 11;
	int scout = cookiePos;
	while (resultPage[scout] != ';')scout++;
	resultPage = resultPage.substr(cookiePos, scout - cookiePos);

	return &resultPage;
}

string *getPageWithCOOKIE(string &JsessionID, string &host, string &directory) {
	resultPage = "";
	request = "GET " + directory + " HTTP/1.1\r\n" +
		"Host: " + host + "\r\n" +
		"Connection:Close\r\n" +
		"Cookie: JSESSIONID=" + JsessionID + "\r\n" +
		"\r\n";

	Send(request, host);
	Sleep(1000);
	Recieve(resultPage);

	closesocket(sock);
	return &resultPage;
}










//send final code 
//UNAVAILIBLE
const string ContentType_HEADER = "\r\nContent-Type: application/x-www-form-urlencoded";
//��Ĭ��content type Ϊ������ʾ
//multipart/form-data ����

//function encodeSource() {
//	document.getElementById("source").value = Base64.encode(document.getElementById("source").value);
//	return true;
//}
//<form method = POST action = submit onsubmit = "return encodeSource()">