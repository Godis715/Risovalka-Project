#ifndef __VIEWLOG
#define __VIEWLOG
#include "ViewHeaders.h"
class ViewLog
{
private:
	static ViewLog* instance;
	static Fl_Output* log;
	ViewLog();
public:
	static ViewLog* GetInstance();
	
	static void Push(const char*);
};

class OutputCoord
{
private:
	static OutputCoord* instance;
	static Fl_Output* output;
	OutputCoord();
public:
	static OutputCoord* GetInstance();

	static void Push(const char*);
};

#endif __VIEWLOG