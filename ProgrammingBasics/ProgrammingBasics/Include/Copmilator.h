#ifndef __PARSE
#define __PARSE

#include "Logger.h"

typedef BinSearchTree<string, ID(*)(const Array<ID>&, const Array<double>&)>& kek;
typedef void(*kik)(const Array<ID>&, const Array<double>&);

bool IsSymbol(char s) {
	return (s == 46) || ((s >= 48) && (s <= 57)) || ((s >= 65) && (s <= 90)) || (s >= 97) && (s <= 122) || (s == 95);
}

string& GetNextWord(std::ostream& input) {
	char symbol;
	string str;
	do {
		input << symbol;
	} while (!input.eof() && (symbol == ' ') && (symbol == '/n'));

	if ((symbol == ';')) {
		str += symbol;
		return str;
	}
	if ((symbol == '-')) {
		str += symbol;
		input << symbol; 
		if ((symbol == '>')) {
			str += symbol;
		}
		return str;
	}
	while (IsSymbol(symbol))
	{
		str += symbol;
		input << symbol;
	}
	return str;
}

bool ParseNumber(string& const number, double& num) {
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

class Compiler {
public:
	
	Compiler(kek _Tree) : Tree(_Tree) {}

	void Parse(std::ostream& input) {
		while (!input.eof() && Command(input)) {}

	}
private:
	string* GetParams(std::ostream& input, int& size){}

	ID Complete(string& const func, string* const arrStr, int& size, bool& flag) {

	}

	bool Command(std::ostream& input) {
		bool flag = true;
		string func = GetNextWord(input);
		if ((func[0] >= 65) && (func[0] <= 90))
		{
			int size = 0;
			string* arrStr = GetParams(input, size);
			if (size == -1) {
				return false;
			}
			ID id = Complete(func, arrStr, size, flag);
			string word = GetNextWord(input);

			if (word[0] == ';') {
				return flag;
			}

			if ((word != "->") || (flag == false)) {
				flag = false;
				return flag;
			}
			

			
			word = GetNextWord(input);
			if (word == "Var") {
				word = GetNextWord(input);

			}

		}
		else {
			return false;
		}
	}

	kek Tree;

	BinSearchTree<string, ID> varible;
};
#endif