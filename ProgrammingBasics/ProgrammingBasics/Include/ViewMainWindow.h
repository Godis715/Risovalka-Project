#ifndef __VIEW_MAINWINDOW
#define __VIEW_MAINWINDOW
#include "ViewHeaders.h"
#include "ViewLog.h"

class MainWindow : public Fl_Window, public DisplayWidjet
{
private:
	static ViewLog* viewLog;

	static Inventory* inventory;
public:
	MainWindow(int, int, const char*);

	~MainWindow();

	int handle(int);
};

#endif __VIEW_MAINWINDOW
