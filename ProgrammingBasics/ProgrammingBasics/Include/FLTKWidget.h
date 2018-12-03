#ifndef __FLTKWidget
#define __FLTKWidget

#include "IWidjet.h"


class FLTKDisplayParamPrim : public IDisplayParamPrim
{
private:
	const std::string password;
public:
	FLTKDisplayParamPrim(const std::string);

	~FLTKDisplayParamPrim();

	void SetParam(const Array<std::string>&, const Array<std::string>&);
};

class FLTKDisplayParamReq : public IDisplayParamReq
{
private:
	const std::string password;
public:
	FLTKDisplayParamReq(const std::string);

	~FLTKDisplayParamReq();

	void SetParam(const Array<std::string>&, const std::string);
};

class FLTKCreatingToolbar : public ICreatingToolbar
{
private:
	const std::string password;
public:
	FLTKCreatingToolbar(const std::string);
	~FLTKCreatingToolbar();

	void SetParam(const Array<std::string>&);

	void Clear();
};

class FLTKRequirementInput : public IRequirementInput
{
private:
	const std::string password;
public:
	FLTKRequirementInput(const std::string);

	~FLTKRequirementInput();
};

class FLTKDrawMode : public IDrawMode
{
private:
	const std::string password;
public:
	FLTKDrawMode(const std::string);
	~FLTKDrawMode();

	void SetName(const std::string);
};

#endif