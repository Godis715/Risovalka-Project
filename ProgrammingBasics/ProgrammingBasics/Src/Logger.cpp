#include "Logger.h"

int Logger::minLevel = LEVEL_3;
std::ostream* Logger::output = nullptr;

string operator + (int num, string str) {
	return std::to_string(num) + str;
}

string operator + (string str, int num) {
	return str + std::to_string(num);
}