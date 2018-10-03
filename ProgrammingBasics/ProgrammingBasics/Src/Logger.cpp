#include "Logger.h"

int Logger::minLevel = LEVEL_3;
std::ostream* Logger::output = nullptr;


string operator + (int num, const string &str) {
	return std::to_string(num) + str;
}

string operator + (const string &str, int num) {
	return str + std::to_string(num);
}
