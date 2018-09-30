#ifndef __IWIDJET
#define __IWIDJET


class IWidjet
{
protected:
	const std::string password;
public:
	IWidjet(const std::string);
};

class IDisplayParam : public IWidjet
{
	Array<std::string> params;
	Array<std::string> reqs;
public:
	IDisplayParam(const std::string);

	~IDisplayParam();

	void SetParam(const Array<std::string>&, const Array<std::string>&);
};

class ICreateToolbar : public IWidjet
{
	Array<std::string> possibleReqs;
public:
	ICreateToolbar(const std::string);

	void SetParam(const Array<std::string>&);
};

class IRequirementInput : public IWidjet
{
public:
	IRequirementInput(const std::string);

	~IRequirementInput();
};

#endif __IWIDJET