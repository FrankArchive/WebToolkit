#ifndef Response_h
#define Response_h
#include"sysfunc.h"

using namespace std;
enum ResponseStatus {
	OK = 200,
	Moved_Permanently = 301,
	Moved_Temporarily = 302,
	Not_Modified = 303,
	Bad_Request = 400,
	Unauthorized = 401,
	Forbidden = 403,
	Not_Found = 404,
	Internal_Server_Error = 500,
	Service_Unaviailable = 503
};
string string_of(int code);
class Response {
	int status;//服务器状态
	map<string, string>key_pool;
	string content;//回复正文
	
	//生成回复前的最后整理
	bool check();
public:
	Response(int stat) {
		status = stat;
	}
	void set_content(string content);
	int set_key(string key, string value);
	string toString();
};
#endif