#ifndef __PARSE
#define __PARSE

#include "Logger.h"
#include <regex>

typedef BinSearchTree<string, ID(*)(const Array<ID>&, const Array<double>&)>& kek;
typedef void(*kik)(const Array<ID>&, const Array<double>&);


class Compiler {
public:
	Compiler(kek _Tree) : Tree(_Tree) {}

	void Parse(std::istream& input) {
		string str;
		while (!input.eof()) {
			str = "";
			char symbol = 'a';
			while ((!input.eof()) && (symbol != ';'))
			{
				input >> symbol;
				str += symbol;
			}
			if (!IsRight(str)) {
				return;
			}
			if (!Command(str)) {
				return;
			}
		}
	}
private:
    bool IsRight(const string& str) {
		std::cmatch result;
		std::regex regul("[A-Z]"
			"([a-z0-9_])*"
			"\\("
			"(([a-z0-9_])*,)*"
			"(([a-z0-9_])*\\))"
			"\\("
			"(([0-9.])*,)*"
			"(([0-9.])*\\))"
			";"
		);
		if (regex_match(str.c_str(), result, regul)) {
			return true;
		}

		std::regex regul2("[A-Z]"
			"([a-z0-9_])*"
			"\\("
			"(([a-z0-9_])*,)*"
			"(([a-z0-9_])*\\))"
			"\\("
			"(([0-9.])*,)*"
			"(([0-9.])*\\))"
			"->"
			"[a-z]"
			"([a-z0-9_])*"
			";"
		);
		if (regex_match(str.c_str(), result, regul2)) {
			return true;
		}
		return false;
	}

	bool IsSymbol(char s) {
		return (s != 47) || ((s >= 45) && (s <= 57)) || ((s >= 65) && (s <= 90)) || (s >= 97) && (s <= 122) || (s == 95);
	}

	string GetNameFunction(string& input) {
		string result = input.substr(0, input.find("("));
		input = input.substr(input.find("("), input.length());
		return result;
	}

    bool ParseNumber(const string& number, double& num) {
		int countPoint = 0;
		if ((number[0] < 48) && (number[0] > 57)) {
			return false;
		}

		for (size_t i = 1; i < number.length(); ++i) {
			if (((number[0] < 48) && (number[0] > 57)) && (number[i] != '.')) {
				return false;
			}
			if (number[i] == '.') {
				++countPoint;
				if (countPoint > 1) {
					return false;
				}
			}
		}
		num = stod(number);
		return true;
	}

	Array<string> GetVaribles(string&  input) {
		Array<string> result;
		int i = 0;
		int j = 0;

		while (input[i] != ')') {
			++i;
			string temp;
			while ((input[i] != ')') && (input[i] != ','))
			{
				temp += input[i];
				++i;
			}
			if (temp != "") {
				result.PushBack(temp);
			}
		}
		input = input.substr(i + 1, input.length());
		return result;
	}

	Array<double> GetPararms(string& input, bool& flag) {
		Array<double> result;
		int i = 0;
		string str;
		while (input[i] != ')') {
			++i;
			while ((input[i] != ')') && (input[i] != ','))
			{
				str += input[i];
				++i;
			}
			double temp;
			if (str != "") {
				if (ParseNumber(str, temp)) {
					result.PushBack(temp);
					str = "";
				}
				else {
					flag = false;
					return result;
				}
			}
		}
		input = input.substr(i + 1, input.length());
		return result;
	}

    ID Complete(const string& func, const Array<string>& variables, const Array<double>& params, bool& flag) {
		ID id;
		double param;

		Array<ID> ids(variables.GetSize());
		for (int j = 0; j < variables.GetSize(); ++j) {
			auto marker = varible.Find(variables[j]);
			if (marker.IsValid()) {
				ids[j] = *marker;
			}
			else {
				flag = false;
				return id;
			}
		}

		return Tree.Find(func).operator*()(ids, params);
	}

	bool Command(string& input) {
		bool flag = true;
		string func = GetNameFunction(input);

		auto varibles = GetVaribles(input);
		
		auto params = GetPararms(input, flag);
		if (!flag) {
			return flag;
		}
		ID id = Complete(func, varibles, params, flag);

		if (!flag) {
			return flag;
		}

		if (input[0] == '-') {
			int x = input.length() - 3;
			input = input.substr(2, input.length() - 3);
			auto marker = varible.Find(input);
			if (marker.IsValid()) {
				marker.Delete();
			}
			varible.Add(input, id);
		}
		return flag;
	}

	kek Tree;

	BinSearchTree<string, ID> varible;
};
#endif
