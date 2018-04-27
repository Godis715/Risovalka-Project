#pragma once
#include <iostream>
#include "Array.h"

class Logger {
private:

	static int sensitivity;

	static std::ostream* output;
	static Logger* instance;
	Logger() { }
public:
	static void InitLogger(std::ostream* _output, int _sensitivity) {
		if (output == nullptr) {
			output = _output;
			sensitivity = _sensitivity;
		}
	}
	static Logger* GetInstance() {
		if (output == nullptr) {
			throw std::exception("Output stream wasn't initialized");
		}
		if (instance == nullptr) {
			instance = new Logger();
		}
		return instance;
	}
	void Log(/*smth, */int priority) { }
};