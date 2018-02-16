#include"Response.h"

bool Response::check() {
	if (content.size() != 0)
		set_key("Content-Length", toStr(content.size()));
	return true;
}
string Response::toString() {
	check();
	string result = (string)"HTTP/1.1 " + toStr(status) + " " + string_of(status) + "\r\n";

	for (unordered_map<string, string>::iterator i = key_pool.begin();
		i != key_pool.end(); i++)
		result += i->first + ":" + i->second + "\r\n";

	result += "\r\n" + content;
	return result;
}

string string_of(int code) {
	switch (code) {
	case 200:return "OK";
	case 301:return "Moved Permanently";
	case 302:return "Moved Temporarily";
	case 303:return "Not Modified";
	case 400:return "Bad Request";
	case 401:return "Unauthorized";
	case 403:return "Forbidden";
	case 404:return "Not Found";
	case 500:return "Internal Server Error";
	case 503:return "Service Unavailable";
	}
	return "UNRECOGNIZED ERROR";
}
