#ifndef __MAILBOX
#define __MAILBOX

#include <queue>
#include <string>
#include "Array.h"

enum Code
{
	draw_point = 0,
	draw_segment,
	draw_circle,
	draw_arc,
	draw_curve,
	properties_point = 10,
	properties_segment,
	properties_circle,
	properties_curve,
	properties_req,
	set_style = 20,
	possible_req,
	translate_scene,
	scale_scene,
	rotate_scene,
	current_draw_mode,
	delete_req_input
};

struct Message {
	Array<double> doubleArr;
	Array<int> intArr;
	Array<std::string> strArr;

	int code;
};

class MailBox {
public:
	void SendMessage(const Message&);
	Message GetMessage();
	bool Empty();

	static MailBox* GetInstance();
private:
	MailBox();

	std::queue<Message> messageQueue;
	static MailBox* instance;
};

#endif
