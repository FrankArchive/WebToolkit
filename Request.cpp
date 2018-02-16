#include"Request.h"
bool Request::check() {
	if (content.size() != 0)
		set_key("Content-Length", toStr(content.size()));
	if (target[0] != '/')target = "/" + target;
	return true;
}
string Request::toString() {
	check();
	string result;
	result +=
		type_dict[type] + " " + target + " " + "HTTP/1.1\r\n";
	for (unordered_map<string, string>::iterator i = key_pool.begin();
		i != key_pool.end(); i++)
		result += i->first + ": " + i->second + "\r\n";

	result += "\r\n" + content;
	return result;
}