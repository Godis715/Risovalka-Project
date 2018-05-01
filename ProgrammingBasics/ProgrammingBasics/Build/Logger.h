#pragma once
#include <iostream>
#include "Array.h"
#include <string>

#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define MAX_LEVEL 3

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

	template <typename T> static void Log(std::string message, int priority) {
		if (priority >= minLevel) {
			(*output) << message << std::endl;
		}
		else {
			return;
		}
	}

	static void Log(std::string message, int priority, int) {
		if (priority >= minLevel) {
			(*output) << message << std::endl;
		}
		else {
			return;
		}
	}
};