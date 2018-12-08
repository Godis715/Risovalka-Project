#ifndef __MAILBOX
#define __MAILBOX

#include <queue>
#include <string>
#include "Array.h"

#include "Presenter.h"

using namespace DrawProject;

namespace Kernel {

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
		properties_arc,
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
		void InitKernel();
		void SendMessage(const Message&);
		void SendEvent(/**/);
		Message GetMessage();
		bool Empty();

		static MailBox* GetInstance();
	private:
		MailBox();

		std::queue<Message> messageQueue;
		static MailBox* instance;
	};
}
#endif
