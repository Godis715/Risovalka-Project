#ifndef __LOGGER
#define __LOGGER

#include <fstream>
#include <string>

using std::string;

namespace DrawProject {


#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define MAX_LEVEL 3

#define LOG Logger::Log
#define LOGERROR Logger::LogError

	class Logger {
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

		static void Log(const char* message, int priority) {
			if (priority >= minLevel) {
				(*output) << "LOG:" << message << std::endl;
			}
			else {
				return;
			}
		}

		static void LogError(const char* message, int priority) {
			if (priority >= minLevel) {
				(*output) << "ERROR:" << message << std::endl;
				system("pause");
				exit(0);
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
