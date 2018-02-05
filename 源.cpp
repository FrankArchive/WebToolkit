#include<iostream>
#include"Response.h"
#include"Request.h"
using namespace std;
int main() {
	Response test1(Response_Status::OK);
	test1.set_content("Nothing");
	cout << test1.toString();

	Request test2(Request_Method::GET);
	test2.set_host("www.baidu.com");
	test2.set_target("home.html");
	test2.set_content("I want...");
	cout << endl << test2.toString();
	return 0;
}