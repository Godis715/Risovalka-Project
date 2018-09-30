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

#endif __VIEWLOG