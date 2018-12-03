#ifndef __MAILBOX
#define __MAILBOX

#include <queue>
#include <string>
#include "Array.h"

struct Message {
	Array<double> doubleArr;
	Array<int> intArr;
	std::string str;

	int code;
};

class MailBox {
public:
	void SendMessage(const Message&);
	Message GetMessage();
	bool HasMessages();

	static MailBox* GetInstance();
private:
	MailBox();

	std::queue<Message> messageQueue;
	static MailBox* instance;
};

#endif
