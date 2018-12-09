#ifndef __MAILBOX
#define __MAILBOX

#include <queue>
#include <string>
#include "Array.h"
#include <exception>

#include "Presenter.h"

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
		DrawProject::Array<double> doubleArr;
		DrawProject::Array<int> intArr;
		DrawProject::Array<std::string> strArr;

		int code;
	};

	class MailBox {
	public:
		void InitKernel();
		void SendMessage(Message*);

		void SendEvent(int code, DrawProject::Array<double>& doubleArr, const std::string& str = "") {
			auto presenter = DrawProject::Presenter::GetInstance();
			std::cout << doubleArr.GetSize();
			std::cout << "string is" << str;

			std::ofstream log("logs.txt");
			try {
				presenter->Set_event(DrawProject::Event(code), doubleArr, str);
			}
			catch (std::exception e) {
				log << e.what();
			}
			log.close();
		}

		Message* GetMessage();
		bool Empty();

		static MailBox* GetInstance();
	private:
		MailBox();

		std::queue<Message*> messageQueue;
		static MailBox* instance;
	};
}
#endif
