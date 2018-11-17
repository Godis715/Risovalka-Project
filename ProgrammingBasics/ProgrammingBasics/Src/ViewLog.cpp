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


OutputCoord::OutputCoord()
{
	if (output == nullptr)
	{
		output = new Fl_Output(520, 630, 490, 30);
	}
}

OutputCoord* OutputCoord::GetInstance() {
	if (instance == nullptr) {
		instance = new OutputCoord();
	}
	return instance;
}

void OutputCoord::Push(const char* _val)
{
	output->value(_val);
}

OutputCoord* OutputCoord::instance = nullptr;
Fl_Output* OutputCoord::output = nullptr;