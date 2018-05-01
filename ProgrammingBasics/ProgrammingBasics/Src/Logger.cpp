#include "Logger.h"

int LoggerStatic::minLevel = LEVEL_1;
std::ostream* LoggerStatic::output = nullptr;

string operator + (int num, string str) {
	return std::to_string(num) + str;
}

string operator + (string str, int num) {
	return str + std::to_string(num);
}