#ifndef __MAILBOX
#define __MAILBOX

#include "List.h"
#include <string>

#define NewRequest RequestController::_NewRequest

class Postcard {
private:
	char* message;
	char* data;
public:
	Postcard(char*, char*);
	~Postcard();
	char* GetMessage();
	char* GetData();
};

class MailBox
{
private:
	List<Postcard> box;
public:
	Postcard GetNextPoscard();
	bool HasPoscards();
	MailBox();
	~MailBox();
};

class BaseRequest {
protected:
	std::string* request;
	void Add(const std::string& partialRequest) {
		*request += partialRequest + "/";
	}
public:
	BaseRequest(string* _request) {
		request = _request;
	}
	BaseRequest(BaseRequest&& base) {
		this->request = base.request;
		base.request = nullptr;
	}
};

class EndClass : public BaseRequest {
public:

	EndClass(std::string* _request) : BaseRequest(_request) {

	}

	Postcard PutParams	(const Array<double>& doubleArr = Array<double>(0),
						const Array<std::string>& strArr = Array<std::string>(0))
	{
		auto postcard = Postcard(*request, doubleArr, strArr);
		delete request;
		return postcard;
	}

	Postcard PutParams(const Array<double>& doubleArr = Array<double>(0),
		const Array<std::string>& strArr = Array<std::string>(0)) {
		auto postcard = Postcard(*request, doubleArr, strArr);
		delete request;
		return postcard;
	}
};


class DrawClass;
#pragma region DrawClass
class LineClass;
class PointClass;
class SegmentClass;
class CircleClass;
#pragma endregion

class PutInfoClass;
#pragma region PutInfoClass
	class StateClass;
#pragma endregion

class RequestClass : public BaseRequest {
private:
public:
	RequestClass(std::string* _request) : BaseRequest(_request) {
		
	}
	
	DrawClass Draw();
	PutInfoClass PutInfo();
};

class RequestController {
public:
	static RequestClass _NewRequest();
};

class DrawClass : public BaseRequest {
private:
public:
	DrawClass(std::string* _request) : BaseRequest(_request) {

	}
	LineClass Line();
	PointClass Point();
	SegmentClass Segment();
	CircleClass Circle();
};

class PutInfoClass : public BaseRequest {
private:
public:
	PutInfoClass(std::string* _request) : BaseRequest(_request) {

	}
	StateClass State();
};

class LineClass : public EndClass {
public:
	LineClass(std::string* _request) : EndClass(_request) {

	}
};
class PointClass : public EndClass {
public:
	PointClass(std::string* _request) : EndClass(_request) {

	}
};
class SegmentClass : public EndClass {
public:
	SegmentClass(std::string* _request) : EndClass(_request) {

	}
};
class CircleClass : public EndClass {
public:
	CircleClass(std::string* _request) : EndClass(_request) {

	}
};

class StateClass : public EndClass {
public:
	StateClass(std::string* _request) : EndClass(_request) {

	}
};



#endif
