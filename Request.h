#ifndef Request_h
#define Request_h
#include"sysfunc.h"

enum RequestMethod{ GET, PST, PUT, DEL };
const string type_dict[4] = { "GET","POST","PUT","DELETE" };

class Request {
	int type; //请求类型，如post
	
	string target;
	unordered_map<string, string>key_pool;
	string content;//回复正文
	
	bool check();
public:
	Request(int request_type) {
		type = request_type;
	}
	void set_host(string host) { set_key("Host", host); }
	void set_target(string targ) { this->target = targ; }
	void set_content(string content) { this->content = content; }
	string get_content() { return content; }
	int set_key(string key, string value) {
		key_pool[key] = value;
		return key_pool.size();
	}
	string toString();
};
#endif