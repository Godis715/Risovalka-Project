#ifndef __IWIDJET
#define __IWIDJET


class IWidjet
{
protected:
	const std::string password;
public:
	IWidjet(const std::string);
	~IWidjet();
};

class IDisplayParamPrim : public IWidjet
{
	Array<std::string> params;
	Array<std::string> reqs;
public:
	IDisplayParamPrim(const std::string);

	~IDisplayParamPrim();

	void SetParam(const Array<std::string>&, const Array<std::string>&);
};

class IDisplayParamReq : public IWidjet
{
public:
	Array<std::string> params;
	std::string reqName;
public:
	IDisplayParamReq(const std::string);

	~IDisplayParamReq();

	void SetParam(const Array<std::string>&, const std::string);
};

class ICreatingToolbar : public IWidjet
{
	Array<std::string> possibleReqs;
public:
	ICreatingToolbar(const std::string);
	~ICreatingToolbar();

	void SetParam(const Array<std::string>&);

	void Clear();
};

class IRequirementInput : public IWidjet
{
public:
	IRequirementInput(const std::string);

	~IRequirementInput();
};

#endif __IWIDJET