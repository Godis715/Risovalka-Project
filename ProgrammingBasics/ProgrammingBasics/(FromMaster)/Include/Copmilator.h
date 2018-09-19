#ifndef __PARSE
#define __PARSE

#include "Logger.h"
#include <regex>

typedef BinSearchTree<string, std::function<ID(const Array<ID>&, const Array<double>&)>> kek;
typedef void(*kik)(const Array<ID>&, const Array<double>&);


class Compiler {
public:
	static void Initializer(kek*);

	static Compiler* GetInstance();

	~Compiler();

	void Parse(std::istream& input);
private:
	static Compiler* _instance;

	Compiler(kek* _Tree);

	bool IsRight(const string& str);

	bool IsSymbol(char s);

	string GetNameFunction(string& input);

	bool ParseNumber(const string& number, double& num);

	Array<string> GetVaribles(string&  input);

	Array<double> GetPararms(string& input, bool& flag);

	ID Complete(const string& func, const Array<string>& variables, const Array<double>& params, bool& flag);

	bool Command(string& input);

	kek* Tree;

	BinSearchTree<string, ID> varible;
};
#endif
