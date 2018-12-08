#ifndef __VIEW_MAINWINDOW
#define __VIEW_MAINWINDOW
#include "ViewHeaders.h"
#include "ViewLog.h"

using namespace DrawProject;

class MainWindow : public Fl_Window, public DisplayWidjet
{
private:
	static ViewLog* viewLog;

	static Inventory* inventory;

	static Presenter* presenter;
public:
	MainWindow(int, int, const char*);

	~MainWindow();

	int handle(int);
};

#endif __VIEW_MAINWINDOW
