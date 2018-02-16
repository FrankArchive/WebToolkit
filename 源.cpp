#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#define DEBUG_SOCKET

#ifdef DEBUG_REQUEST_RESPONSE
#include"Response.h"
#include"Request.h"
int main() {
	Response test1(ResponseStatus::OK);
	test1.set_content("Nothing");
	cout << test1.toString();

	Request test2(RequestMethod::GET);
	test2.set_host("www.baidu.com");
	test2.set_target("home.html");
	test2.set_content("I want...");
	cout << endl << test2.toString();
	return 0;
}
#endif


#ifdef DEBUG_PARSER
#include"Parser.h"
void read(string &a) {
	string temp;
	while (getline(cin, temp))a +=temp+ "\r\n";
}
int main() {
	string a;
	read(a);
	Request *b=0;
	RequestParser test(a);
	if (test.is_success())b = test.get();
	if (b)
		b->set_content("new content"),
		cout << b->toString();
}
#endif

#ifdef DEBUG_SOCKET
#include"SocketWrapper.h"
#include"Request.h"
#include"Parser.h"
int main() {
	Request req(0);
	req.set_host("www.baidu.com");
	req.set_key("Content-Type", "application/x-www-form-urlencoded");
	req.set_key("Connection", "Keep-Alive");
	req.set_key("Pragma", "no-cache");
	req.set_key("Accept", "text/html, application/xhtml+xml, */*");
	req.set_target("/");
	cout << req.toString();
	SocketPool pool;
	pool.add_client("www.baidu.com");
	Socket *obj = pool["www.baidu.com"];
	obj->perform_send(req.toString());
	obj->perform_recieve();

	FILE *a = fopen("a.html", "w");
	string output = obj->get_result();
	RequestParser b(output);
	output = b.get()->get_content();
	fprintf(a, "%s", output.c_str());
	cout << obj->get_result();
	fclose(a); delete a;
}
#endif