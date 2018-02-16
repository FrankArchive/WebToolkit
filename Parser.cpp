#include"Parser.h"
int parse_line(string &message, int current) {
	int flag = current;
	while (message[flag++] != '\r');
	return flag-1;
}
bool RequestParser::parse() {
	result = new Request(0);//just for DEBUG!!!!
	int next = parse_line(message,current), colon;
	
	current = next + 2;
	while (message[current] != '\r') {
		next = parse_line(message, current);
		for (colon = current; message[colon] != ':'&&colon < next; colon++);
		if (colon == next)return 1;
		result->set_key(
			tidy(message.substr(current, colon - current)), 
			tidy(message.substr(colon + 1, next - colon - 1))
		);
		current = next + 2;
	}
	
	result->set_content(message.substr(current + 2, message.size() - current - 3));//may be a mistake
	return 0;
}