#ifndef __LOGGER
#define __LOGGER

#include <fstream>
#include <string>
#include <iostream>

using std::string;

namespace DrawProject {


#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define MAX_LEVEL 4

#define LOG Logger::Log
#define LOGERROR Logger::LogError

	class Logger {
	private:

		static int minLevel;
		static std::ostream* output;


	public:
		static void InitLogger(std::ostream* _output, int _sensitivity) {
			output = _output;
			minLevel = _sensitivity;
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

		template <typename T> static void Log(std::string message, const T& value, int priority) {
			if (priority >= minLevel) {
				(*output) << message << " " << value << std::endl;
			}
			else {
				return;
			}
		}

		template <class T1, class T2> static void Log(std::string message, const T1& val1, const T2& val2, int priority) {
			if (priority >= minLevel) {
				(*output) << message << " " << val1 << ' ' << val2 << std::endl;
			}
			else {
				return;
			}
		}

		static void Log(std::string message, int priority) {

			if (priority >= minLevel) {
				(*output) << "LOG:" << message << '\n';
			}
			else {
				return;
			}
		}

		static void LogError(const char* message, int priority) {
			if (priority >= minLevel) {
				(*output) << "ERROR:" << message << std::endl;
				std::cout << message;
			}
			else {
				return;
			}
		}
	};

	string operator + (int num, string str);

	string operator + (string str, int num);

}
#endif
