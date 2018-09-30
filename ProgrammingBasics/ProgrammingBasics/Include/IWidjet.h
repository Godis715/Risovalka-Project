#ifndef __IWIDJET
#define __IWIDJET

class Widjet
{
protected:
	const string password;
public:
	Widjet(const string);
};

class DisplayParam : public Widjet
{
	Array<string> params;
	Array<string> reqs;
public:
	DisplayParam(const string);

	void AddParam(const Array<string>&);

	void AddRequirements(const Array<string>&);
};

class CreateToolbar : public Widjet
{
	Array<string> possibleReqs;
public:
	CreateToolbar(const string);

	void AddPossibleReqs(const Array<string>&);
};

#endif __IWIDJET