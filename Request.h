#ifndef Request_h
#define Request_h
#include"sysfunc.h"
using std::string; using std::vector; using std::map;

enum RequestMethod{ GET, POST, PUT, DELETE };
const string type_dict[4] = { "GET","POST","PUT","DELETE" };

class Request {
	int type; //�������ͣ���post
	
	string host, target;
	map<string, string>key_pool;
	string content;//�ظ�����
	
	bool check();
public:
	Request(int request_type) {
		type = request_type;
	}
	void set_host(string host) { this->host = host;	}
	void set_target(string targ) { this->target = targ; }
	void set_content(string content) { this->content = content; }
	int set_key(string key, string value) {
		key_pool[key] = value;
		return key_pool.size();
	}
	
	string toString();
};
#endif