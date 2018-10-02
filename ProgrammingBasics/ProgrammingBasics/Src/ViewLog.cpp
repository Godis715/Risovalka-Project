#include "ViewLog.h"

ViewLog::ViewLog()
{
	if (log == nullptr)
	{
		log = new Fl_Output(1010, 0, 300, 30);//1010
	}
}

ViewLog* ViewLog::GetInstance() {
	if (instance == nullptr) {
		instance = new ViewLog();
	}
	return instance;
}

void ViewLog::Push(const char* _val)
{
	log->value(_val);
}

ViewLog* ViewLog::instance = nullptr;
Fl_Output* ViewLog::log = nullptr;