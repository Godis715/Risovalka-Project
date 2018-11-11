#include "Compilator.h"

Compiler::Compiler(treeFunc* _Tree) : Tree(_Tree) {}

Compiler::~Compiler() {
	delete Tree;
}

void Compiler::Initializer(treeFunc* _Tree) {
	if (_instance != nullptr) {
		delete _instance;
	}
	_instance = new Compiler(_Tree);
}

Compiler* Compiler::GetInstance() {
	if (_instance == nullptr) {
		// $$$
	}
	return _instance;
}

void Compiler::Parse(std::istream& input) {
	string str;
	while (!input.eof()) {
		str = "";
		char symbol = 'a';
		while ((!input.eof()) && (symbol != ';'))
		{
			input >> symbol;
			str += symbol;
		}
		if (!Command(str)) {
			return;
		}
	}
}

bool Compiler::Command(string& str) {
	std::cmatch result;
	std::regex createPrim("[A-Z]"
		"([a-z])*"
		"\\("
		"(([0-9.])*,)*"
		"(([0-9.])*\\))"
		"->\\("
		"([a-z]([a-z0-9_])*,)*"
		"([a-z]([a-z0-9_])*\\))*"
		";"
	);
	if (regex_match(str.c_str(), result, createPrim)) {
		return CommandCreatePrim(str);
	}

	std::regex createReq("[A-Z]"
		"([a-z_])*"
		"\\("
		"([a-z]([a-z0-9_])*,)*"
		"([a-z]([a-z0-9_])*\\))*"
		"\\("
		"(([0-9.])*,)*"
		"(([0-9.])*\\))"
		"->"
		"[a-z]([a-z0-9_])*"
		";"
	);
	if (regex_match(str.c_str(), result, createReq)) {
		return CommandCreateReq(str);
	}

	std::regex change("[A-Z]"
		"([a-z])*"
		"\\("
		"(([a-z0-9_])*,)*"
		"(([a-z0-9_])*\\))"
		"\\("
		"(([0-9.])*,)*"
		"(([0-9.])*\\))"
		";"
		);
	if (regex_match(str.c_str(), result, change)) {
		return CommandChange(str);
	}

	std::regex del("Delete"
		"\\("
		"([a-z]([a-z0-9_])*,)*"
		"([a-z]([a-z0-9_])*\\))*"
		";"
		);
	if (regex_match(str.c_str(), result, del)) {
		return CommandDel(str);;
	}
	return false;
}

bool Compiler::IsSymbol(char s) {
	return (s != 47) || ((s >= 45) && (s <= 57)) || ((s >= 65) && (s <= 90)) || (s >= 97) && (s <= 122) || (s == 95);
}

string Compiler::GetNameFunction(string& input) {
	string result = input.substr(0, input.find("("));
	input = input.substr(input.find("("), input.length());
	return result;
}

bool Compiler::ParseNumber(const string& number, double& num) {
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

Array<string> Compiler::GetVaribles(string&  input) {
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

Array<double> Compiler::GetPararms(string& input, bool& flag) {
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

Array<ID> Compiler::Complete(const string& func, const Array<string>& variables, const Array<double>& params, bool& flag) {
	double param;

	Array<ID> ids(variables.GetSize());
	for (int j = 0; j < variables.GetSize(); ++j) {
		auto marker = varible.Find(variables[j]);
		if (marker.IsValid()) {
			ids[j] = *marker;
		}
		else {
			flag = false;
			return Array<ID>(0);
		}
	}

	auto marker = Tree->Find(func);
	if (marker.IsValid()) {
		return marker.operator*()(ids, params);
	}
	else {
		flag = false;
		return Array<ID>(0);
	}
}

bool Compiler::CommandCreatePrim(string& input) {
	bool flag = true;
	string func = GetNameFunction(input);

	auto params = GetPararms(input, flag);
	if (!flag) {
		return flag;
	}
	Array<ID> IDs = Complete(func, Array<string>(0), params, flag);

	if (!flag) {
		return flag;
	}
	input = input.substr(2, input.length() - 3);
	auto varibles = GetVaribles(input);
	for (int i = 0; i < varibles.GetSize(); ++i) {
		auto marker = varible.Find(varibles[i]);
		if (marker.IsValid()) {
			marker.Delete();
		}
		varible.Add(varibles[i], IDs[i]);
	}
	return flag;
}

bool Compiler::CommandCreateReq(string& input) {
	bool flag = true;
	string func = GetNameFunction(input);
	auto varibles = GetVaribles(input);
	auto params = GetPararms(input, flag);
	Array<ID> IDs = Complete(func, varibles, params, flag);

	if (!flag) {
		return flag;
	}
	input = input.substr(2, input.length() - 3);
	varible.Add(input, IDs[0]);
	return flag;
}

bool Compiler::CommandChange(string& input) {
	bool flag = true;
	string func = GetNameFunction(input);
	auto varibles = GetVaribles(input);
	auto params = GetPararms(input, flag);
	Array<ID> IDs = Complete(func, varibles, params, flag);
	return flag;
}

bool Compiler::CommandDel(string& input) {
	bool flag = true;
	string func = GetNameFunction(input);
	auto varibles = GetVaribles(input);
	Array<ID> IDs = Complete(func, varibles, Array<double>(0), flag);
	return flag;
}

Compiler* Compiler::_instance = nullptr;