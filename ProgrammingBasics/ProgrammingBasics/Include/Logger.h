#pragma once
#include <iostream>
#include "Array.h"
#include <string>

#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define MAX_LEVEL 3

#define VAR_VALUE 4

#define LOG LoggerStatic::Log
using std::string;

class Logger {
private:

	int minLevel;
	std::ostream* output;

	static Logger* instance;
	Logger() { }
public:
	void InitLogger(std::ostream* _output, int _sensitivity) {
		if (output == nullptr) {
			output = _output;
			minLevel = _sensitivity;
		}
	}

	void SetSensitivity(int _level) {
		if (_level > MAX_LEVEL) {
			_level = MAX_LEVEL;
		}
		if (_level > LEVEL_1) {
			_level = LEVEL_1;
		}

		minLevel = _level;
	}

	static Logger* GetInstance() {
		if (instance == nullptr) {
			instance = new Logger();
		}
		return instance;
	}

	void Log(std::string message, int priority) {
		if (priority >= minLevel) {
			(*output) << "MESSAGE: " << message << std::endl;
		}
		else {
			return;
		}
	}

};

static class LoggerStatic {
private:

	static int minLevel;
	static std::ostream* output;

public:
	static void InitLogger(std::ostream* _output, int _sensitivity) {
		if (output == nullptr) {
			output = _output;
			minLevel = _sensitivity;
		}
	}

	static void SetSensitivity(int _level) {
		if (_level > MAX_LEVEL) {
			_level = MAX_LEVEL;
		}
		if (_level > LEVEL_1) {
			_level = LEVEL_1;
		}

		minLevel = _level;
	}

	static void Log(string message, int priority) {
		if (priority < minLevel) {
			return;
		}
		(*output) << message << std::endl;
	}
	template <typename T> static void Log(string name, const T& value, int priority) {
		if (priority < minLevel) {
			return;
		}
		(*output) << "var " << name << " = " << value << std::endl;
	}
};



string operator + (int num, string str);
string operator + (string str, int num);